#include "m2dxdirect3d.h"

M2DXDirect3D* M2DXDirect3D::instance = nullptr;

M2DXDirect3D* M2DXDirect3D::getInstance()
{
	if (!instance)
	{
		instance = new M2DXDirect3D();
	}

	return instance;
}

M2DXDirect3D::M2DXDirect3D() : d3dInterface(nullptr), d3dDeviceInterface(nullptr), d3dBackBuffer(nullptr), d3dSurface(nullptr) { }

M2DXDirect3D::~M2DXDirect3D()
{
	release();
}

void M2DXDirect3D::release()
{
	if (d3dBackBuffer)
	{
		d3dBackBuffer->Release();
		d3dBackBuffer = nullptr;
	}
	if (d3dSurface)
	{
		d3dSurface->Release();
		d3dSurface = nullptr;
	}

	if (d3dDeviceInterface)
	{
		d3dDeviceInterface->Release();
		d3dDeviceInterface = nullptr;
	}

	if (d3dInterface)
	{
		d3dInterface->Release();
		d3dInterface = nullptr;
	}

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool M2DXDirect3D::init(HWND hWnd, M2DXSize windowSize)
{
	// Create Direct3D interface.
	d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3dInterface)
	{
		return false;
	}

	// Create struct to hold various device information.
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = DEFAULT_BACK_BUFFER_FORMAT;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = windowSize.width;
	d3dpp.BackBufferHeight = windowSize.height;

	// Create device class.
	d3dInterface->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDeviceInterface);
	if (!d3dDeviceInterface)
	{
		return false;
	}

	// Get back buffer.
	d3dDeviceInterface->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &d3dBackBuffer);

	// Create surface.
	d3dDeviceInterface->CreateOffscreenPlainSurface(windowSize.width, windowSize.height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &d3dSurface, NULL);
	if (!d3dSurface)
	{
		return false;
	}

	return true;
}
