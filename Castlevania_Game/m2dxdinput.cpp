#include "m2dxdinput.h"

M2DXDInput* M2DXDInput::instance = nullptr;

M2DXDInput* M2DXDInput::getInstance()
{
	if (!instance)
	{
		instance = new M2DXDInput();
	}

	return instance;
}

M2DXDInput::M2DXDInput() : diInterface(nullptr), diKeyboard(nullptr) { }

M2DXDInput::~M2DXDInput()
{
	release();
}

void M2DXDInput::release()
{
	if (diKeyboard)
	{
		diKeyboard->Unacquire();
		diKeyboard->Release();
	}

	if (diInterface)
	{
		diInterface->Release();
	}

	if (instance)
	{
		delete instance;
	}
}

bool M2DXDInput::init(HINSTANCE hInstance, HWND hWnd)
{
	// Create DirectInput interface.
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&diInterface, NULL);
	if (!diInterface)
	{
		return false;
	}

	// Create keyboard device.
	diInterface->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
	if (!diKeyboard)
	{
		return false;
	}

	// Set cooperative level.
	diKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	// Set device data format.
	diKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// Set device properties.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DEFAULT_KEYBOARD_BUFFER_SIZE;

	auto result = diKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK)
	{
		return false;
	}

	// Acquire the keyboard.
	result = diKeyboard->Acquire();
	if (result != DI_OK)
	{
		return false;
	}

	return true;
}
