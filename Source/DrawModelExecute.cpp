#include "DrawModelExecute.h"
#include "VMTHooks.h"
#include "Entity.h"
#include "Materials.h"
#include "CDraw.h"
#include "CMat.h"

#include "Visuals.h"

void __stdcall Hooked_DrawModelExecute(
	const DrawModelState_t &state,
	const ModelRenderInfo_t &pInfo,
	matrix3x4 *pCustomBoneToWorld )
{
	VMTManager& hook = VMTManager::GetHook(gBase.ModelRender);
	auto CallOriginal = hook.GetMethod<DrawModelExecuteFn>((int)e_offset::DrawModelExecute);
	try
	{
		if (pInfo.pModel)
			gVisuals.DrawModelExecute(state, pInfo, pCustomBoneToWorld, CallOriginal);
	}
	catch (...)
	{
		MessageBox(NULL, "Failed Hooked_DrawModelExecute()", "Error", MB_OK);
		return CallOriginal(gBase.ModelRender, state, pInfo, pCustomBoneToWorld);
	}
	CallOriginal(gBase.ModelRender, state, pInfo, pCustomBoneToWorld);
	gMat.ResetMaterial();
}