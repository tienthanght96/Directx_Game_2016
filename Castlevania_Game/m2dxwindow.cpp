#include "m2dxwindow.h"

M2DXWindow* M2DXWindow::instance = nullptr;

M2DXWindow* M2DXWindow::getInstance()
{
	if (!instance)
	{
		instance = new M2DXWindow();
	}

	return instance;
}

M2DXWindow::M2DXWindow() : windowSize(0, 0), hWnd(nullptr) { }

M2DXWindow::~M2DXWindow()
{
	release();
}

void M2DXWindow::release()
{
	if (hWnd)
	{
		hWnd = nullptr;
	}

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool M2DXWindow::init(HINSTANCE hInstance, LPCSTR windowName, M2DXSize windowSize)
{
	// Register window class.
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = windowName;

	RegisterClassEx(&wc);

	// Create window.
	hWnd = CreateWindowEx(NULL, windowName, windowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_DEFAULT, windowSize.width, windowSize.height, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return false;
	}

	this->windowSize = windowSize;

	return true;
}

LRESULT CALLBACK M2DXWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
