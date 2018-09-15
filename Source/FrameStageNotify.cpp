#include "FrameStageNotify.h"
#include "Entity.h"
#include "Visuals.h"
#include "VMTHooks.h"

void __stdcall Hooked_FrameStageNotify(ClientFrameStage_t curStage)
{
	auto &hook = VMTManager::GetHook(gBase.Client);
	try
	{
		gVisuals.FrameStageNotify(curStage);
	}
	catch (...)
	{
		MessageBox(NULL, "Failed Hooked_FrameStageNotify()", "ERROR", MB_OK);
	}
	VMTManager::GetHook(gBase.Client).GetMethod<void(__thiscall *)(PVOID, ClientFrameStage_t)>((int)e_offset::FrameStageNotify)(gBase.Client, curStage);
}