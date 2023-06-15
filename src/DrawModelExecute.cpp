#include "DrawModelExecute.h"
#include "VMTHooks.h"
#include "Entity.h"
#include "Materials.h"
#include "CDraw.h"
#include "CMat.h"

#include "Visuals.h"

bool drawModel = true;

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
	if (drawModel)
		CallOriginal(gBase.ModelRender, state, pInfo, pCustomBoneToWorld);
	drawModel = true;
	gMat.ResetMaterial();
}

bool __fastcall Hooked_ShouldDraw(IClientRenderable* Renderable) {
	if (gVisuals.scopefix.value)
		return true;

	VMTManager& hook = VMTManager::GetHook(Renderable);
	return hook.GetMethod<ShouldDrawFn>((int)e_offset::ShouldDraw)(Renderable);
}
