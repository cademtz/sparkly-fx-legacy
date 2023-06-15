//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef IMATERIALPROXY_H
#define IMATERIALPROXY_H
#pragma once

class IMaterial;
class KeyValues;

class IMaterialProxy
{
public:
	virtual bool Init(IMaterial* pMaterial, KeyValues *pKeyValues) = 0;
	virtual void OnBind(void *) = 0;
	virtual void Release() = 0;
	virtual IMaterial *	GetMaterial() = 0;

protected:
	// no one should call this directly
	virtual ~IMaterialProxy() {}
};

#endif // IMATERIALPROXY_H