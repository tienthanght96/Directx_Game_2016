#pragma once

#include "m2dxutil.h"
#include "m2dxtexture.h"

class M2DXD3DX
{
public:
	static M2DXD3DX* getInstance();

	~M2DXD3DX();

	bool init(LPDIRECT3DDEVICE9 d3dDeviceInterface);

	inline LPD3DXSPRITE getD3DXSpriteInterface() { return d3dxSpriteInterface; }

	M2DXTexture* createTextureWithFile(LPCSTR fileName);

private:
	static M2DXD3DX* instance;

	M2DXD3DX();

	void release();

	LPD3DXSPRITE d3dxSpriteInterface;
};
