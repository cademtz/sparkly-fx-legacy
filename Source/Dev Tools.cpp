#include "Dev Tools.h"
#include "Entity.h"
#include "CDraw.h"

CDevTools gDevTools;

void CDevTools::DrawEntity(CBaseEntity * Entity)
{
	if (!enabled.value)
		return;
	
	Vector origin = Entity->GetAbsOrigin(), screen;
	if (!gDraw.WorldToScreen(origin, screen)) // Can we draw this entity?
		return;

	int nextline = -14; // Help stack the text
	if (ent_type.value)
		gDraw.DrawString(screen.x, screen.y + (nextline += 14), SColor(255), Entity->GetClientClass()->chName);
	if (ent_index.value)
		gDraw.DrawString(screen.x, screen.y + (nextline += 14), SColor(255), to_string((int)Entity->Type()));
}