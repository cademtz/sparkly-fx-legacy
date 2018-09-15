#include "Base.h"

DWORD WINAPI AttachThread(LPVOID lpArguments)
{
	if (gBase.Client != NULL) // Prevent repeat callings.
		return 0;

	gBase.GetInterfaces();
	gOffsets.GetOffsets();
	gBase.HookInterfaces();

	return 1;
}

#include "Menu.h"
BOOL APIENTRY DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, 0, AttachThread, NULL, 0, NULL);

	return true;
}