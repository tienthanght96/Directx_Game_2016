#pragma once

#include "m2dxbasesprite.h"
#include "m2dxbasegamelayer.h"
#include "BatScreen.h"
#include "SceneManager.h"
#include "Intro.h"

#define SCALE_FACTOR 2.0f

class TileScreen : public M2DXBaseGameLayer
{
public:
	TileScreen() {};
	~TileScreen() {};
	BatScreen* bat;
	M2DXBaseSprite screen;
	M2DXBaseSprite pushEnter;
	int colorAlpha = 0;
	void Init() override;
	void update(int deltaTime) override ;
	void render() override;
	void processInput(BYTE keyState[]) override;
	void onKeyDown(int keyCode) override {};
	void release() override;
private:
	bool isEnter = false;
	int remainingChangeColor = 4;
	int remainingChangeScene = 2000;
	void updateColor();
	void changeScene(int deltaTime);

};