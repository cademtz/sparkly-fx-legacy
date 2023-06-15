#include "VGUI.h"
#include "Entity.h"
#include "Panels.h"
#include "CDraw.h"
#include "VMTHooks.h"

#include "Menu.h"
#include "Visuals.h"
#include "Dev Tools.h"

CScreenSize gScreenSize;

VPANEL FindPanel(VPANEL Parent, const char* szName);

//===================================================================================
void __fastcall Hooked_PaintTraverse( PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	VMTManager& hook = VMTManager::GetHook(pPanels);
	auto Original = hook.GetMethod<void(__thiscall*)(PVOID, unsigned int, bool, bool)>((int)e_offset::PaintTraverse);

	try
	{
		static VPANEL FocusOverlay = 0, BaseViewport = 0, HudScope = 0, HudScopeCharge = 0, HudDeath = 0;
		const char* szPanel = gBase.Panels->GetName(vguiPanel);
		if (vguiPanel)
		{
			if (!FocusOverlay && !strcmp(szPanel, "FocusOverlayPanel"))
			{
				// Gets FocusOverlayPanel ID to avoid constantly string comparing
				FocusOverlay = vguiPanel;
				Intro();
			}
			else if (!BaseViewport && gBase.Engine->IsInGame())
			{
				VPANEL parent = gBase.Panels->GetParent(FocusOverlay); // Get root panel
				if (gBase.Panels->HasParent(FocusOverlay, parent) && (BaseViewport = FindPanel(parent, "CBaseViewport")))
				{
					HudScope = FindPanel(BaseViewport, "HudScope");
					HudScopeCharge = FindPanel(BaseViewport, "HudScopeCharge");
					HudDeath = FindPanel(BaseViewport, "HudDeathNotice");
				}
			}
		}

		if (BaseViewport && (gVisuals.killfeed.value || gVisuals.noscope.value))
		{
			int count = gBase.Panels->GetChildCount(BaseViewport);
			for (int i = 0; i < count; i++)
			{
				if (vguiPanel == gBase.Panels->GetChild(BaseViewport, i))
				{
					if (gVisuals.noscope.value && (vguiPanel == HudScope || vguiPanel == HudScopeCharge))
						return;
					if (gVisuals.killfeed.value && vguiPanel != HudDeath &&
						(gVisuals.noscope.value || vguiPanel != HudScope))
							return; // Remove all HUD elements except scope (depending on scope option)
				}
			}
		}

		Original(pPanels, vguiPanel, forceRepaint, allowForce);

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

		if (gBase.Engine->IsInGame())
		{
			// Main entity loop, will skip all players
			for (size_t i = gBase.Engine->GetMaxClients() + 1; i <= gBase.EntList->GetHighestEntityIndex(); i++)
			{
				CBaseEntity* ent = GetBaseEntity(i);
				if (!ent || ent->IsDormant())
					continue; // Avoid null pointers and entities that haven't updated

				gDevTools.DrawEntity(ent);
			}
		}

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
void Intro()
{
	gDraw.Init();
	gMat.Initialize();
	InitTextures();
	GetAllNetvars();

	gMenu.CreateGUI();

	// It is a good day
	gBase.Engine->ClientCmd_Unrestricted("echo Sparkly FX has successfully injected!");
}

VPANEL FindPanel(VPANEL Parent, const char* szName)
{
	if (!strcmp(gBase.Panels->GetName(Parent), szName))
		return Parent;

	for (int i = 0; i < gBase.Panels->GetChildCount(Parent); i++)
	{
		VPANEL panel = gBase.Panels->GetChild(Parent, i);
		if (panel = FindPanel(panel, szName))
			return panel;
	}

	return 0; // Failed to find panel
}