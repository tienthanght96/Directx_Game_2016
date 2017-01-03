#pragma once

#include "m2dxutil.h"
#include "m2dxwindow.h"
#include "m2dxdirect3d.h"
#include "m2dxdinput.h"
#include "m2dxresourcemanager.h"
#include "m2dxdsound.h"

#define MAXIMUM_FRAME_RATE 60

class M2DXBaseGameLayer
{
public:
	M2DXBaseGameLayer() {};
	M2DXBaseGameLayer(HINSTANCE hInstance);
	~M2DXBaseGameLayer();
	virtual bool init(); // Override this method in derived class to prepare the game.
	virtual void Init() {};
	int isKeyDown(int keyCode,BYTE keyState[]);
	void start();

	void Pause() {};

	virtual void update(int deltaTime); // Override this method in derived class to handle game logics

	virtual void render(); // Override this method in derived class to handle game drawings.

	virtual void processInput(BYTE keyState[]); // // Override this method in derived class to handle game keyboard inputs.
	virtual void onKeyDown(int keyCode); // Override this method in derived class to handle game keyboard inputs.
	virtual void onKeyUp(int keyCode); // Override this method in derived class to handle game keyboard inputs.
	virtual void release();
	BYTE  keyStates[256]; // DirectInput keyboard state buffer.
private:
	HINSTANCE hInstance;

	M2DXWindow* window;

	M2DXDirect3D* direct3D;

	M2DXDInput* dinput;

	void draw();

	void processKeyboard();
};
