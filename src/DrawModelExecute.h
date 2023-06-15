#pragma once
#include "Base.h"

struct DrawModelState_t;
struct ModelRenderInfo_t;
typedef float matrix3x4[3][4];
class IClientRenderable;

typedef void(__thiscall *DrawModelExecuteFn)(CModelRender*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
typedef bool(__thiscall* ShouldDrawFn)(IClientRenderable*);

extern bool drawModel; // bad coding but I'm REALLY rushed today

void __stdcall Hooked_DrawModelExecute (
	const DrawModelState_t &state,
	const ModelRenderInfo_t &pInfo,
	matrix3x4 *pCustomBoneToWorld = NULL );

bool __fastcall Hooked_ShouldDraw(IClientRenderable* Renderable);