#include "FrameStageNotify.h"
#include "Entity.h"
#include "Visuals.h"
#include "VMTHooks.h"
#include "DrawModelExecute.h"

void __stdcall Hooked_FrameStageNotify(ClientFrameStage_t curStage)
{
	auto &hook = VMTManager::GetHook(gBase.Client);
	try
	{
		gVisuals.FrameStageNotify(curStage);
		if (curStage == FRAME_RENDER_START)
		{
			if (CBaseEntity* ent = GetBaseEntity(me))
			{
				int& fovPtr = *(int*)((UINT_PTR)ent + nPlayer.m_iFOV), & defaultFov = *(int*)((UINT_PTR)ent + nPlayer.m_iDefaultFOV);
				if (gVisuals.nozoom.value)
				{
					*(float*)((UINT_PTR)ent + nPlayer.m_flFOVRate) = 0;
					fovPtr = defaultFov;
				}
				//else if (fov.value && !(You->Conditions() & tf_cond::TFCond_Zoomed))
					//fovPtr = fov.value;

				// getvfunc screams if you just want void* ... :thinking:
				if (getvfunc<decltype(Hooked_ShouldDraw)*>(ent->GetRenderable(), (int)e_offset::ShouldDraw) != &Hooked_ShouldDraw)
				{
					auto hk = new VMTBaseManager(ent->GetRenderable());
					hk->HookMethod(&Hooked_ShouldDraw, e_offset::ShouldDraw);
					hk->Rehook();
				}

				for (int i = 1; i <= gBase.EntList->GetHighestEntityIndex(); i++)
				{
					CBaseEntity* hat = GetBaseEntity(i);
					if (!hat || hat->GetFollowedEntity() != ent)
						continue;

					if (getvfunc<decltype(Hooked_ShouldDraw)*>(hat->GetRenderable(), (int)e_offset::ShouldDraw) != &Hooked_ShouldDraw)
					{
						auto hk = new VMTBaseManager(hat->GetRenderable());
						hk->HookMethod(&Hooked_ShouldDraw, e_offset::ShouldDraw);
						hk->Rehook();
					}
				}
			}
		}
	}
	catch (...)
	{
		MessageBox(NULL, "Failed Hooked_FrameStageNotify()", "ERROR", MB_OK);
	}
	VMTManager::GetHook(gBase.Client).GetMethod<void(__thiscall *)(PVOID, ClientFrameStage_t)>((int)e_offset::FrameStageNotify)(gBase.Client, curStage);
}