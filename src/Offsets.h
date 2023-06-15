#pragma once
#include <Windows.h>

#define CHECKPTR(Pointer) (gOffsets.SafetyCheck(Pointer))
class COffsets
{
public:
	void GetOffsets();

	DWORD LoadFromBuffer;
	DWORD KeyValues;
	DWORD ParentEnt;

	void SafetyCheck(void* Pointer)
	{
		if (Pointer)
			return;

		MessageBox(NULL, "Sparkly failed to get a super important pointer thingy!\nThe program will now exit.", "Fatal error", MB_OK);
		exit(EXIT_FAILURE);
	}
	inline void SafetyCheck(DWORD Pointer)
	{
		return SafetyCheck((void*)Pointer);
	}
};
extern COffsets gOffsets;