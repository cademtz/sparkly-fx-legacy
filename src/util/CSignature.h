#pragma once
#include "Base.h"

class CSignature
{
public:
	DWORD dwFindPattern(DWORD dwAddress, DWORD dwLength, const char* szPattern);
	HMODULE GetModuleHandleSafe( const char* pszModuleName );
	DWORD FromClient ( char* chPattern );
	DWORD FromEngine ( char* chPattern );
};

extern CSignature gSig;
