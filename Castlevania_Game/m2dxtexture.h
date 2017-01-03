#pragma once

#include "m2dxutil.h"

class M2DXTexture
{
public:
	M2DXTexture(LPDIRECT3DTEXTURE9 texture, M2DXSize textureSize);
	~M2DXTexture();

	inline LPDIRECT3DTEXTURE9 getTexture() { return texture; }

	inline M2DXSize getTextureSize() { return textureSize; }

private:
	LPDIRECT3DTEXTURE9 texture;

	M2DXSize textureSize;
};
