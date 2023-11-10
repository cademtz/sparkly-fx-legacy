#pragma once
#include "Base.h"

struct DrawModelState_t;
struct ModelRenderInfo_t;
typedef float matrix3x4[3][4];
class IClientRenderable;
struct StaticPropRenderInfo_t;

typedef void(__thiscall *DrawModelExecuteFn)(CModelRender*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
typedef int(__thiscall *DrawModelExStaticPropFn)(CModelRender*, ModelRenderInfo_t&);
typedef int (__thiscall* DrawStaticPropArrayFastFn)(CModelRender*, StaticPropRenderInfo_t *pProps, int count, bool bShadowDepth);
typedef bool(__thiscall* ShouldDrawFn)(IClientRenderable*);

extern bool drawModel; // bad coding but I'm REALLY rushed today
extern bool drawStaticProps;

void __stdcall Hooked_DrawModelExecute (
	const DrawModelState_t &state,
	const ModelRenderInfo_t &pInfo,
	matrix3x4 *pCustomBoneToWorld = NULL );

int __stdcall Hooked_DrawStaticPropArrayFast(StaticPropRenderInfo_t *pProps, int count, bool bShadowDepth);

bool __fastcall Hooked_ShouldDraw(IClientRenderable* Renderable);