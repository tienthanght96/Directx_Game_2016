#include "m2dxd3dx.h"

M2DXD3DX* M2DXD3DX::instance = nullptr;

M2DXD3DX* M2DXD3DX::getInstance()
{
	if (!instance)
	{
		instance = new M2DXD3DX();
	}

	return instance;
}

M2DXD3DX::M2DXD3DX() : d3dxSpriteInterface(nullptr) { }

M2DXD3DX::~M2DXD3DX()
{
	release();
}

bool M2DXD3DX::init(LPDIRECT3DDEVICE9 d3dDeviceInterface)
{
	// Create sprite interface.
	D3DXCreateSprite(d3dDeviceInterface, &d3dxSpriteInterface);
	if (!d3dxSpriteInterface)
	{
		return false;
	}

	return true;
}

void M2DXD3DX::release()
{
	if (d3dxSpriteInterface)
	{
		d3dxSpriteInterface->Release();
		d3dxSpriteInterface = nullptr;
	}

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

M2DXTexture* M2DXD3DX::createTextureWithFile(LPCSTR fileName)
{
	if (!d3dxSpriteInterface)
	{
		return nullptr;
	}

	LPDIRECT3DTEXTURE9 d3dTexture = nullptr;

	// Get device.
	LPDIRECT3DDEVICE9 d3dDeviceInterface;
	d3dxSpriteInterface->GetDevice(&d3dDeviceInterface);

	// Get image information.
	D3DXIMAGE_INFO imageInfo;
	auto result = D3DXGetImageInfoFromFile(fileName, &imageInfo);
	if (result != S_OK)
	{
		return nullptr;
	}

	// Create texture from file.
	D3DXCreateTextureFromFileEx(d3dDeviceInterface, fileName, imageInfo.Width, imageInfo.Height, 1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 254), &imageInfo, NULL, &d3dTexture);
	if (!d3dTexture)
	{
		return nullptr;
	}

	M2DXTexture* texture = new M2DXTexture(d3dTexture, M2DXSize(imageInfo.Width, imageInfo.Height));
	return texture;
}
