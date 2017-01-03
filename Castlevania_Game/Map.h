#pragma once

#include "m2dxbasesprite.h"
#include "m2dxbasegamelayer.h"
#include "SceneManager.h"
#include "BossFromMap.h"
#include "Castlevania.h"
#include "m2dxdsound.h"

#define SCALE_FACTOR 2.0f

class Map : public M2DXBaseGameLayer
{
public:
	Map(int level)
	{
		_level = level;
	};
	Map() {};
	~Map() {};
	M2DXBaseSprite map;
	M2DXBaseSprite simonFromMap;
	BossFromMap *boss;
	void Init() override;
	void update(int deltaTime) override;
	void render() override;
	void processInput(BYTE keyState[]) override {};
	void onKeyDown(int keyCode) override {};
	void release() override {};
private:
	void updateSimon(int deltaTime);
	SimonBelmont* simonIntro;
	void updateFrame(int deltaTime);
	int remainingChangeFrame = 200;
	bool frame1 = true;
	int _level;
	int remainingChangeColor = 4;
	int remainingChangeScene = 2000;
};