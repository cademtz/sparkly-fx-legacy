#include "Visuals.h"
#include "Engine.h"
#include "Materials.h"
#include <unordered_map>

CVisuals gVisuals;

// - Using old and new world materials to efficiently decide when to set / reset our colors
// - For now, not optimized very well at all
unordered_map<MaterialHandle_t, SColor> worldmats_new, worldmats_old;

void CVisuals::FrameStageNotify(ClientFrameStage_t Stage)
{
	bool bReset = !gBase.Engine->IsInGame() || !world_enabled.value;
	if (bReset && worldmats_old.size())
	{
		if (gBase.Engine->IsInGame())
		{
			for (auto& hMat : worldmats_old) // Reset the material colors
			{	
				IMaterial* mat = gBase.MatSystem->GetMaterial(hMat.first);
				if (!mat)
					continue;

				SColor color = hMat.second;
				float blend[4] = { (float)color[0] / 255.f, (float)color[1] / 255.f, (float)color[2] / 255.f, (float)color[3] / 255.f };
				mat->ColorModulate(blend[0], blend[1], blend[2]);
				mat->AlphaModulate(blend[3]);
			}
		}

		worldmats_new.clear();	// Clear cache of materials
		worldmats_old.clear();	//
	}

	if (!world_enabled.value || Stage != FRAME_NET_UPDATE_POSTDATAUPDATE_END)
		return;

	for (MaterialHandle_t i = gBase.MatSystem->FirstMaterial(); i != gBase.MatSystem->InvalidMaterial(); i = gBase.MatSystem->NextMaterial(i))
	{
		IMaterial* mat = gBase.MatSystem->GetMaterial(i);
		if (!mat)
			continue;

		bool bIsSkybox = !strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX);
		if (!bIsSkybox && strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_WORLD))
			continue;

		if (worldmats_new.find(i) == worldmats_new.end())
		{
			float r, g, b, a = mat->GetAlphaModulation();
			mat->GetColorModulation(&r, &g, &b);

			SColor old_color(r * 255.f, g * 255.f, b * 255.f, a * 255.f);
			worldmats_old.emplace(i, old_color);
			worldmats_new.emplace(i, old_color);
		}

		SColor color = worldmats_old.at(i);
		if (bIsSkybox)
			color = sky_clr.bDef ? SColor(255) : sky_clr.color;
		else
			color = world_clr.bDef ? SColor(255) : world_clr.color;

		if (worldmats_new.at(i) != color)
		{
			float blend[4] = { (float)color[0] / 255.f, (float)color[1] / 255.f, (float)color[2] / 255.f, (float)color[3] / 255.f };
			mat->ColorModulate(blend[0], blend[1], blend[2]);
			mat->AlphaModulate(blend[3]);

			worldmats_new.at(i) = color;
		}
	}
}

// These hardcoded color arrays will be improved later

static SColor colors_team[] =
{
	SColor(0), //Dummy
	SColor(160), // 1 Teamone (UNUSED)
	SColor(186, 52, 53), // 2 Red
	SColor(0, 128, 255), // 3 Blu
	SColor(0) // 4 Teamfour (UNUSED) 
};

static SColor colors_team_light[] =
{
	SColor(0), //Dummy
	SColor(160), // 1 Teamone (UNUSED)
	SColor(240, 100, 90), // 2 Red
	SColor(100, 150, 240), // 3 Blu
	SColor(0) // 4 Teamfour (UNUSED) 
};

#include "Entity.h"
#include "CMat.h"
void CVisuals::DrawModelExecute(
	const DrawModelState_t &state,
	const ModelRenderInfo_t &pInfo,
	matrix3x4 *pCustomBoneToWorld,
	DrawModelExecuteFn Original )
{
	if (!player_enabled.value)
		return;

	CBaseEntity* entity;
	if (!(entity = GetBaseEntity(pInfo.entity_index)))
		return;
	ent_id type = entity->Type();
	if (type != ent_id::CTFPlayer && type != ent_id::CTFWearable)
		return;

	// Normal visibility will just run once
	// And "Always" visibility will run twice with the same mat
	bool bReset = player_enabled.value > 2;

	// Stubbed for now. More materials later.
	Matptr desired = gMat.glow;
	if (!desired)
		return;

	byte team = entity->Team();
	SColor color = player_mat.bDef ? colors_team_light[team] : player_mat.color;
	if (type == ent_id::CTFWearable)
	{
		if (!hat_enabled.value)
			return;
		else if (hat_enabled.value == 2)
			color = hat_mat.bDef ? colors_team[team] : hat_mat.color;
	}

	desired->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, player_enabled.value != 1);
	gMat.ForceMaterial(color, desired);

	// "Behind walls" / "always" requires a second render with ignorez before the original
	if (player_enabled.value != 1)
	{
		Original(gBase.ModelRender, state, pInfo, pCustomBoneToWorld);
		if (player_enabled.value == 2) // Now we will render a normal visibility model with "always" enabled
			desired->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	}

	if (bReset)
		gMat.ResetMaterial();
}