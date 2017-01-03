#pragma once

#include "SimonBelmont.h"
#include "CObject.h"
#include "Box.h"
#include "SweptAABB.h"

#define HOLY_WATER_SPRITE "Resources\\Sprites\\Weapons\\HolyWater\\HolyWaterSheet.png"
#define HOLY_WATER_SHEET "Resources\\Sprites\\Weapons\\HolyWater\\HolyWaterSheet"

#define HOLY_WATER_ANIMATE_RATE 8

#define GRAVITY 0.00048828125F

#define HOLY_WATER_X 0.0525F
#define HOLY_WATER_Y 0.1875F

#define HOLY_WATER_FRAME_1 "HolyWaterFrame1"
#define HOLY_WATER_FRAME_2 "HolyWaterFrame2"
#define HOLY_WATER_FRAME_3 "HolyWaterFrame3"
#define HOLY_WATER_FRAME_4 "HolyWaterFrame4"

#define HOLY_WATER_WIDTH 20
#define HOLY_WATER_HEIGHT 20

class HolyWater : public M2DXAnimatedSprite, CObject
{
public:
	HolyWater(int X, int Y, bool AD);
	~HolyWater();

	Box getBox()
	{
		Box temp(getPositionX() * 2, getPositionY() * 2, getSize().width * 2, getSize().height * 2);
		return temp;
	}
	void Update(int deltaTime, CObject* simon);

	void Draw() override;

protected:
	string getNextFrame() override;
	int getAnimateRate() override { return HOLY_WATER_ANIMATE_RATE; }

private:
	D3DXVECTOR2 velocity;
	int remainingDead = 1000;
	SweptAABB *swept = new SweptAABB();
	void updateState(int deltaTime);
	void updateInfor();
	void updatePosition(CObject* simon, int deltaTime);
};