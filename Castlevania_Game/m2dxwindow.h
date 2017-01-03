#pragma once

#include "m2dxutil.h"

#define DEFAULT_WINDOW_WIDTH 512
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_WINDOW_SIZE M2DXSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)

#define DEFAULT_WINDOW_NAME "Castle Vania"

class M2DXWindow
{
public:
	static M2DXWindow* getInstance();

	~M2DXWindow();

	bool init(HINSTANCE hInstance, LPCSTR windowName, M2DXSize windowSize);

	inline M2DXSize getWindowSize() { return windowSize; }

	inline HWND getWindow() { return hWnd; }

private:
	static M2DXWindow* instance;

	M2DXWindow();

	void release();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // Used to init window.

	M2DXSize windowSize;

	HWND hWnd;
};
