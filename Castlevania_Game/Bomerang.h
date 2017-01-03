#pragma once

#include "CObject.h"
#include "Box.h"
#include "SweptAABB.h"

#define BOMERANG_SPRITE "Resources\\Sprites\\Weapons\\Bomerang\\BomerangSheet.png"
#define BOMERANG_SHEET "Resources\\Sprites\\Weapons\\Bomerang\\BomerangSheet"

#define BOMERANG_ANIMATE_RATE 20

#define GRAVITY 0.00048828125F

#define VELOCITY 0.3875F

#define TIME_TO_CHANGE_STATE 300

#define BOMERANG_FRAME_1 "BomerangFrame1"
#define BOMERANG_FRAME_2 "BomerangFrame2"
#define BOMERANG_FRAME_3 "BomerangFrame3"

#define BOMERANG_WIDTH 30
#define BOMERANG_HEIGHT 28

class Bomerang : public M2DXAnimatedSprite, CObject
{

public:
	Bomerang(int X, int Y, bool AD);
	~Bomerang();

	void Update(int deltaTime, CObject* simon);

	void Draw() override;

protected:
	string getNextFrame() override;
	int getAnimateRate() override { return BOMERANG_ANIMATE_RATE; }

private:
	bool canChange = true;
	void updateDirection();
	void updateVelocityX(int deltaTime);
	void updateBomerangState(CObject* simon);
	D3DXVECTOR2 velocity;
	SweptAABB *swept = new SweptAABB();
	void updateInfor();
	void updatePosition( int deltaTime);
};