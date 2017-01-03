
#pragma once

#include "m2dxbasesprite.h"
#include "m2dxbasegamelayer.h"
#include "SceneManager.h"

#define SCALE_FACTOR 2.0f

#define TIME_UPDATE_SCREEN 0

class PauseScene : public M2DXBaseGameLayer
{
public:
	PauseScene() {};
	~PauseScene() {};
	M2DXBaseSprite screen;
	M2DXBaseSprite btnResune;
	M2DXBaseSprite btnRestart;
	M2DXBaseSprite btnExit;
	M2DXBaseSprite gameOver;
	void Init() override;
	void update(int deltaTime) override;
	void render() override;
	void processInput(BYTE keyState[]) override;
	void onKeyDown(int keyCode) override;
	void release() override;
private:
	bool isEnter;
	int currentButton;
	int remainingUpdateScreen;
	int colorAlpha = 0;
	int colorAlphaResume = 0;
	int colorAlphaRestart = 0;
	int colorAlphaExit = 0;
	int colorAlphaText = 0;
	void updateColor();
	void updateScreen(int deltatime);
	void updateResume();
	void updateRestart();
	void updateExit();
	void updateText();
	void drawButton();
};