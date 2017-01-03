#pragma once

#include "m2dxutil.h"

#define DEFAULT_KEYBOARD_BUFFER_SIZE 128

class M2DXDInput
{
public:
	static M2DXDInput* getInstance();

	~M2DXDInput();

	bool init(HINSTANCE hInstance, HWND hWnd);

	inline LPDIRECTINPUT8 getDInputInterface() { return diInterface; }
	inline LPDIRECTINPUTDEVICE8 getKeyboard() { return diKeyboard; }

private:
	static M2DXDInput* instance;

	M2DXDInput();

	void release();

	LPDIRECTINPUT8 diInterface;
	LPDIRECTINPUTDEVICE8 diKeyboard;
};
