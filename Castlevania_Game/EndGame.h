#pragma once

#include "m2dxbasesprite.h"
#include "m2dxbasegamelayer.h"
#include "SceneManager.h"

#define TIME_DESTROY 0
#define TIME_CHANGE_SLIDE 1000

#define SCALE_FACTOR 2.0f

class EndGame : public M2DXBaseGameLayer
{
public:
	EndGame() {};
	~EndGame() {};
	M2DXBaseSprite screen;
	M2DXBaseSprite castle;
	vector<M2DXBaseSprite*> produce;
	void Init() override;
	void update(int deltaTime) override;
	void render() override;
	void processInput(BYTE keyState[]) override;
	void onKeyDown(int keyCode) override {};
	void release() override;
private:
	int colorA;
	bool isVisible;
	void updateProduce(int deltaTime);
	void initProduce();
	void drawProduce();
	void updateCastle(int deltaTime);
	int remainingDestroy;
	int remainingBegin;
	int remainingChangeSlide;
	M2DXPoint castlePoint;
};