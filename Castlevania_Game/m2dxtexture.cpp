#include "m2dxtexture.h"

M2DXTexture::M2DXTexture(LPDIRECT3DTEXTURE9 texture, M2DXSize textureSize) : texture(texture), textureSize(textureSize) { }

M2DXTexture::~M2DXTexture()
{
	if (texture)
	{
		texture->Release();
		texture = nullptr;
	}
}
