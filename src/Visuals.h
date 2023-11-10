#pragma once
#include "Controls.h"
#include "DrawModelExecute.h"

enum ClientFrameStage_t;
class CPlayer;

class CVisuals
{
public:
	// World settings

	Checkbox world_enabled = Checkbox("Enabled");
	Checkbox props_enabled = Checkbox("Draw props", true);
	ColorPicker world_clr = ColorPicker("World color", SColor(200));
	ColorPicker sky_clr = ColorPicker("Sky color", SColor(200));

	// Player effects

	Listbox player_enabled = Listbox("Player materials", { "Disabled", "Default visibility", "Always visible", "Only through walls"}, 0);
	Listbox hat_enabled = Listbox("Hat override", { "Disabled", "Same as player", "Hat color" }, 0);
	ColorPicker player_mat = ColorPicker("Player color", SColor(200));
	ColorPicker hat_mat = ColorPicker("Hat color", SColor(200));

	// Heads-up display

	Checkbox killfeed = Checkbox("Killfeed only");
	Checkbox nozoom = Checkbox("No scope zoom");
	Checkbox noscope = Checkbox("No scope overlay");
	Checkbox scopefix = Checkbox("Draw scoped player");

	// Filters

	Checkbox fplayer = Checkbox("Players only");
	Checkbox fview = Checkbox("Viewmodel only");

	void FrameStageNotify(ClientFrameStage_t Stage);
	void DrawModelExecute(
		const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo,
		matrix3x4 *pCustomBoneToWorld,
		DrawModelExecuteFn Original );
	int DrawStaticPropArrayFast( StaticPropRenderInfo_t *pProps, int count, bool bShadowDepth );
};

extern CVisuals gVisuals;