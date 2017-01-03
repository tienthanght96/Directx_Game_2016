#pragma once

#include "m2dxutil.h"

#define DEFAULT_BACK_BUFFER_FORMAT D3DFMT_X8R8G8B8

class M2DXDirect3D
{
public:
	static M2DXDirect3D* getInstance();

	~M2DXDirect3D();

	bool init(HWND hWnd, M2DXSize windowSize);

	inline LPDIRECT3D9 getD3DInterface() { return d3dInterface; }
	inline LPDIRECT3DDEVICE9 getD3DDeviceInterface() { return d3dDeviceInterface; }
	inline LPDIRECT3DSURFACE9 getD3DSurface() { return d3dSurface; }
	inline LPDIRECT3DSURFACE9 getD3DBackBuffer() { return d3dBackBuffer; }

private:
	static M2DXDirect3D* instance;

	M2DXDirect3D();

	void release();

	LPDIRECT3D9 d3dInterface;
	LPDIRECT3DDEVICE9 d3dDeviceInterface;
	LPDIRECT3DSURFACE9 d3dBackBuffer;
	LPDIRECT3DSURFACE9 d3dSurface;
};
