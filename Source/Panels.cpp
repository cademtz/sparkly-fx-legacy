#include "VGUI.h"
#include "Engine.h"
#include "Panels.h"
#include "CDraw.h"
#include "VMTHooks.h"

#include "Menu.h"

CScreenSize gScreenSize;
//===================================================================================
void __fastcall Hooked_PaintTraverse( PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	try
	{
		VMTManager& hook = VMTManager::GetHook(pPanels);
		hook.GetMethod<void(__thiscall*)(PVOID, unsigned int, bool, bool)>((int)e_offset::PaintTraverse)(pPanels, vguiPanel, forceRepaint, allowForce);

		static unsigned int FocusOverlay = 0;
		if (!FocusOverlay && vguiPanel && !strcmp(gBase.Panels->GetName(vguiPanel), "FocusOverlayPanel"))
		{
			// Gets FocusOverlayPanel ID to avoid constantly string comparing
			FocusOverlay = vguiPanel;
			Intro();
		}

		if (FocusOverlay != vguiPanel || gBase.Engine->IsDrawingLoadingImage())
			return;

		gBase.Panels->SetTopmostPopup(FocusOverlay, true);

		// ========== This can be improved. It just prevents screen resolution changes from destroying all fonts ========== //
		CScreenSize newSize;
		gBase.Engine->GetScreenSize(newSize.width, newSize.width);
		if (newSize.width != gScreenSize.width || newSize.height != gScreenSize.height)
			gDraw.Reload();
		// ========== Update your input FIRST to enable usage throughout your program ========== //
		gMenu.GetInput();
		// - Other code here that requires input can go here
		// ========== Menu code must be called AFTER everything else draws ========== //
		gMenu.Draw();
		gBase.Panels->SetMouseInputEnabled(vguiPanel, gMenu.enabled);
		// ========== I may or may not remove this and find a better method. Call after you're done with input ========== //
		gMenu.EndInput();
	}
	catch(...)
	{
		MessageBox(NULL, "Failed Hooked_PaintTraverse()", "Error", MB_OK);
	}
}
//===================================================================================

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !! Do NOT forget to initialize your menu, fonts, textures, etc.	!!
// !! This is required for the menu to work							!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include "Netvars.h"
#include "CMat.h"
void Intro( void )
{
	gDraw.Init();
	gMat.Initialize();
	InitTextures();
	GetAllNetvars();

	gMenu.CreateGUI();

	// It is a good day
	gBase.Engine->ClientCmd_Unrestricted("echo Sparkly FX has successfully injected!");
}