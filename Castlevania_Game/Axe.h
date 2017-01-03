#pragma once

#include "SimonBelmont.h"
#include "CObject.h"
#include "Box.h"
#include "SweptAABB.h"

#define AXE_SPRITE "Resources\\Sprites\\Weapons\\Axe\\AxeSheet.png"
#define AXE_SHEET "Resources\\Sprites\\Weapons\\Axe\\AxeSheet"

#define AXE_ANIMATE_RATE 8

#define GRAVITY 0.00048828125F

#define VELOCITY_X 0.0825F
#define VELOCITY_Y 0.1875F

#define AXE_FRAME_1 "AxeFrame1"
#define AXE_FRAME_2 "AxeFrame2"
#define AXE_FRAME_3 "AxeFrame3"
#define AXE_FRAME_4 "AxeFrame4"

#define AXE_WIDTH 32
#define AXE_HEIGHT 32

class Axe : public M2DXAnimatedSprite, CObject
{
public:
	Axe(int X, int Y, bool AD);
	~Axe();

	Box getBox()
	{
		Box temp(getPositionX() * 2, getPositionY() * 2, getSize().width * 2, getSize().height * 2);
		return temp;
	}
	void Update(int deltaTime, CObject* simon);

	void Draw() override;

protected:
	string getNextFrame() override;
	int getAnimateRate() override { return AXE_ANIMATE_RATE; }

private:
	D3DXVECTOR2 velocity;
	SweptAABB *swept = new SweptAABB();
	void updateInfor();
	void updatePosition(CObject* simon, int deltaTime);
};