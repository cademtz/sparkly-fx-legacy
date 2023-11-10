#include "Base.h"
#include "VMTHooks.h"
#include "CSignature.h"
#include "Engine.h"

CBaseManager gBase;

bool CBaseManager::GetInterfaces()
{
	// Grab the client module first, since it is loaded after everything else
	CreateInterface ClientFactory;
	while (1)
	{
		ClientFactory = CreateInterface("client.dll", false);
		if (ClientFactory.instance)
			break;
		Sleep(1000); // Wait for the client DLL to be loaded
	}
	if (!ClientFactory.instance)
		gBase.Fatal("Fatal error", "Sparkly FX was unable to find the client module!%s", "\nThe program will now exit.");

	CreateInterface EngineFactory("engine.dll");
	CreateInterface VGUIFactory("vguimatsurface.dll");
	CreateInterface CVarFactory("vstdlib.dll");
	CreateInterface MaterialSystemFactory("MaterialSystem.dll");
	CreateInterface VGUI2Factory("vgui2.dll");

	GameEventManager = (IGameEventManager2*)	EngineFactory("GAMEEVENTSMANAGER002");
	ModelRender = (CModelRender*)				EngineFactory("VEngineModel016");
	EngineTrace = (IEngineTrace*)				EngineFactory("EngineTraceClient003");
	RenderView = (CRenderView*)					EngineFactory("VEngineRenderView014");
	Prediction = (CPrediction*)					ClientFactory("VClientPrediction001");
	MatSystem = (CMaterialSystem*)				MaterialSystemFactory("VMaterialSystem081");
	ModelInfo = (IVModelInfo*)					EngineFactory("VModelInfoClient006");
	Surface = (ISurface*)						VGUIFactory("VGUI_Surface030");
	EntList = (CEntList*)						ClientFactory("VClientEntityList003");
	Engine = (EngineClient*)					EngineFactory("VEngineClient013");
	Panels = (IPanel*)							VGUI2Factory("VGUI_Panel009");
	Client = (CHLClient*)						ClientFactory("VClient017");
	Cvar = (ICvar*)								CVarFactory("VEngineCvar004");

	DWORD clientmodeScan = gSig.FromClient("8B 0D ? ? ? ? 8B 02 D9 05"), globalsScan = gSig.FromClient("A3 ? ? ? ? 8D 45 08 6A 01 50 E8");
	if (!clientmodeScan || !globalsScan)
		gBase.Fatal("Fatal error", "Sparkly's signatures are outdated!%s", "\nThe program will now exit.");

	Globals = **(CGlobals***)(globalsScan + 1);
	ClientMode = **(ClientModeShared***)(clientmodeScan + 2);

	Engine->ClientCmd_Unrestricted("echo Sparkly FX: Grabbed interfaces...");
	return true;
}

#include "Menu.h"
#include "Panels.h"
#include "FrameStageNotify.h"
#include "DrawModelExecute.h"

void CBaseManager::HookInterfaces()
{
	VMTBaseManager* panelHook = new VMTBaseManager(gBase.Panels);
	panelHook->HookMethod(&Hooked_PaintTraverse, e_offset::PaintTraverse);
	panelHook->Rehook();

	VMTBaseManager* chlHook = new VMTBaseManager(gBase.Client);
	chlHook->HookMethod(&Hooked_FrameStageNotify, e_offset::FrameStageNotify);
	chlHook->Rehook();

	VMTBaseManager* modelHook = new VMTBaseManager(gBase.ModelRender);
	modelHook->HookMethod(&Hooked_DrawModelExecute, e_offset::DrawModelExecute);
	modelHook->HookMethod(&Hooked_DrawStaticPropArrayFast, e_offset::DrawStaticPropArrayFast);
	modelHook->Rehook();

	while (!(hwnd = FindWindowA("Valve001", NULL)))
		Sleep(500);
	gMenu.windowProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&Hooked_WndProc);

	Engine->ClientCmd_Unrestricted("echo Sparkly FX: Hooked stuff...");
}

#include "Engine.h"
COffsets gOffsets;
void COffsets::GetOffsets()
{
	// Add signatures here
	CHECKPTR(KeyValues = gSig.FromEngine("FF 15 ? ? ? ? 83 C4 08 89 06 8B C6"));
	CHECKPTR(LoadFromBuffer = gSig.FromEngine("55 8B EC 83 EC 38 53 8B 5D 0C"));
	CHECKPTR(ParentEnt = gSig.FromClient("E8 ? ? ? ? 8B F8 85 FF 75 07 33 C0"));

	KeyValues -= 0x42;
	ParentEnt = *(size_t*)(ParentEnt + 1) + ParentEnt + 5;

	gBase.Engine->ClientCmd_Unrestricted("echo Sparkly FX: Got signatures...");
}

CreateInterface::CreateInterface(const char* szModule, bool handleError)
{
	instance = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(szModule), "CreateInterface");
	if (!instance && handleError)
		gBase.Fatal("Fatal error", "Failed to get a CreateInterface handle to '%s'!%s", szModule, "\nThe program will now exit.");
}
void* CreateInterface::operator()(const char* pName, int* pReturnCode)
{
	void* result = instance(pName, pReturnCode);
	if (!result)
		gBase.Fatal("Fatal error", "Failed to get '%s' interface!%s", pName, "\nThe program will now exit.");

	return result;
}

void CBaseManager::Fatal(const char* szTitle, const char* szMessage, ...)
{
	va_list va_alist;
	char szBuffer[256] = { 0 };

	va_start(va_alist, szMessage);
	vsprintf_s(szBuffer, szMessage, va_alist);
	va_end(va_alist);

	MessageBoxA(NULL, szBuffer, szTitle, MB_OK);
	exit(EXIT_FAILURE);
}