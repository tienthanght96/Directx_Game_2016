#pragma once

#define SMALL_HEART_SPRITE "Resources\\Sprites\\SmallHeart\\SmallHeartSheet.png"

#include "m2dx.h"
#include "DoorManager.h"
#include "Brick.h"
#include "SimonBelmont.h"
#include "CameraFlat.h"
#include "BackgroundLoader.h"
#include "Quadtree.h"
#include "ItemManager.h"
#include "WeponManager.h"
#include "ScoreManager.h"
#include "Time.h"
#ifndef SCALE_FACTOR
#define SCALE_FACTOR 2.0F
#endif

class Castlevania : public M2DXBaseGameLayer
{	
public:
	Castlevania();
	Castlevania(int nextLevel) { nowLevel = nextLevel; };
	~Castlevania();
	BackgroundLoader *bg;
	Quadtree* quad;
	void Init() override;

protected:
	int deltatime;
	void update(int deltaTime) override;
	void render() override;
	void processInput(BYTE keyState[]) override;
	void onKeyDown(int keyCode) override;
private:
	SweptAABB swept;
	void clearAll();
	bool endMap = false;
	bool bossDead = false;
	int remainingChangeState = 2000;
	void setCam(int deltaTime);
	int nowLevel;
	bool isUpArrow = false;;
	int remainingTime = 30;
	void updateTime(int deltaTime);
	void getCamFlat(int &id, int &x, int &y, int &width, int &height, string information);
};