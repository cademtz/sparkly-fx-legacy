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
	ColorPicker world_clr = ColorPicker("World color", SColor(200));

	// Player effects

	Listbox player_enabled = Listbox("Player materials", { "Disabled", "Default visibility", "Always visible", "Only through walls"}, 1);
	Listbox hat_enabled = Listbox("Hat override", { "Disabled", "Same as player", "Hat color" },  1);
	ColorPicker player_mat = ColorPicker("Player color", SColor(200));
	ColorPicker hat_mat = ColorPicker("Hat color", SColor(200));

	void FrameStageNotify(ClientFrameStage_t Stage);
	void DrawModelExecute(
		const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo,
		matrix3x4 *pCustomBoneToWorld,
		DrawModelExecuteFn Original );
};

extern CVisuals gVisuals;