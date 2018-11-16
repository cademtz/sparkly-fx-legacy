#pragma once
#include "Controls.h"

class CDevTools
{
public:
	// Main

	Checkbox enabled = Checkbox("Enabled");

	// Entities

	Checkbox ent_type = Checkbox("Show class types");
	Checkbox ent_index = Checkbox("Show class IDs");

	void DrawEntity(CBaseEntity* Entity);
};

extern CDevTools gDevTools;