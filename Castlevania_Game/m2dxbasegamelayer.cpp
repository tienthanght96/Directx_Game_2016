#include "m2dxbasegamelayer.h"
#include "SceneManager.h"
#include "Castlevania.h"
#include "TileScreen.h"

M2DXBaseGameLayer::M2DXBaseGameLayer(HINSTANCE hInstance) : hInstance(hInstance)
{
	window = M2DXWindow::getInstance();

	direct3D = M2DXDirect3D::getInstance();

	dinput = M2DXDInput::getInstance();
}

M2DXBaseGameLayer::~M2DXBaseGameLayer()
{
	release();
}

void M2DXBaseGameLayer::release()
{
	if (hInstance)
	{
		hInstance = nullptr;
	}

	M2_SAFE_DELETE(window);

	M2_SAFE_DELETE(direct3D);

	M2_SAFE_DELETE(dinput);
}


bool M2DXBaseGameLayer::init()
{
	if (!window->init(hInstance, DEFAULT_WINDOW_NAME, DEFAULT_WINDOW_SIZE))
	{
		return false;
	}

	if (!direct3D->init(window->getWindow(), window->getWindowSize()))
	{
		return false;
	}

	if (!dinput->init(hInstance, window->getWindow()))
	{
		return false;
	}

	if (!M2DXDSound::getInstance()->init(window->getWindow()))
	{
		return false;
	}

	G_Device = M2DXDirect3D::getInstance()->getD3DDeviceInterface();

	if (!M2DXD3DX::getInstance()->init(M2DXDirect3D::getInstance()->getD3DDeviceInterface()))
	{
		return false;
	}
	if (!M2DXResourceManager::getInstance()->init())
	{
		return false;
	}
	ScoreManager::getInstance()->InitializeState();
	SceneManager::getInstance()->AddElement(new TileScreen());	
	BackgroundLoader::getInstance()->LoadResource();
	Quadtree::getInstance()->load();
	return true;
}
void M2DXBaseGameLayer::start()
{
	MSG msg;

	auto lastTime = GetTickCount();

	DWORD minimumFrameTime = 1000 / MAXIMUM_FRAME_RATE;

	// Show window.
	ShowWindow(window->getWindow(), SW_SHOWNORMAL);

	// Main loop.
	while (true)
	{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				break;
			}

			// Game run.
			DWORD currentTime = GetTickCount();
			auto deltaTime = currentTime - lastTime;
			if (deltaTime >= minimumFrameTime)
			{
				// Update and render the game.
				if (deltaTime > 60)
					deltaTime = 60;
				SceneManager::getInstance()->Update(deltaTime);
				draw();

				lastTime = currentTime;
			}

			// Process keyboard.
			processKeyboard();
	}
}

void M2DXBaseGameLayer::update(int deltaTime) { }

void M2DXBaseGameLayer::draw()
{
	auto d3dDeviceInterface = direct3D->getD3DDeviceInterface();

	d3dDeviceInterface->BeginScene();

	SceneManager::getInstance()->Render();

	d3dDeviceInterface->EndScene();

	// Display the created frame.
	d3dDeviceInterface->Present(NULL, NULL, NULL, NULL);
}

void M2DXBaseGameLayer::render()
{
	/*auto d3dDeviceInterface = direct3D->getD3DDeviceInterface();*/

	// Clear the window to black.
	/*d3dDeviceInterface->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0);*/

	/*auto d3dBackBuffer = direct3D->getD3DBackBuffer();
	auto d3dSurface = direct3D->getD3DSurface();

	d3dDeviceInterface->StretchRect(d3dSurface, NULL, d3dBackBuffer, NULL, D3DTEXF_NONE);*/
}

void M2DXBaseGameLayer::processKeyboard()
{
	auto diKeyboard = dinput->getKeyboard();

	// Collect all key states first
	diKeyboard->GetDeviceState(sizeof(keyStates), keyStates);

	if (isKeyDown(DIK_ESCAPE,keyStates))
		PostMessage(window->getWindow(), WM_QUIT, 0, 0);

	// Collect all buffered events
	DWORD dwElements = DEFAULT_KEYBOARD_BUFFER_SIZE;
	DIDEVICEOBJECTDATA keyEvents[DEFAULT_KEYBOARD_BUFFER_SIZE];
	diKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	SceneManager::getInstance()->HandleInput(keyStates);
	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		auto keyCode = keyEvents[i].dwOfs;
		auto keyState = keyEvents[i].dwData;
		if ((keyState & 0x80) > 0)
		{
			SceneManager::getInstance()->onKeyDown(keyCode);
		}
		else
		{
			onKeyUp(keyCode);
		}
	}
}

int M2DXBaseGameLayer::isKeyDown(int keyCode,BYTE keyState[])
{
	return (keyState[keyCode] & 0x80) > 0;
}

void M2DXBaseGameLayer::processInput(BYTE keyState[]) { }

void M2DXBaseGameLayer::onKeyDown(int keyCode) { }

void M2DXBaseGameLayer::onKeyUp(int keyCode) { }
