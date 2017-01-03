#pragma once

#include "m2dxbasesprite.h"
#include "m2dxbasegamelayer.h"
#include "BatIntro.h"
#include "SceneManager.h"
#include "Castlevania.h"
#include "Map.h"

#define SCALE_FACTOR 2.0f

class Intro : public M2DXBaseGameLayer
{
public:
	Intro() {};
	~Intro() {};
	void Init() override;
	void update(int deltaTime) override;
	void render() override;
	void processInput(BYTE keyState[]) override {};
	void onKeyDown(int keyCode) override {};
	void release() override {};
private:
	M2DXBaseSprite screen;
	M2DXBaseSprite cloud;
	SimonBelmont* simonIntro;
	BlackBat* bat1;
	BlackBat* bat2;
	void changeScene(int deltaTime);
	void updateSimon(int deltaTime);
	int remainingChangeColor = 4;
	int remainingChangeScene = 3000;
};