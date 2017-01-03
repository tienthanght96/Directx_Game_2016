#pragma once

#include "m2dxbasesprite.h"
#include "m2dxanimatedsprite.h"

#define BAT_FRAME_1 "BlackBatFrame1"
#define BAT_FRAME_2 "BlackBatFrame2"


#define BAT_SHEET "Intro\\BlackBatSheet"


class BlackBat : public M2DXAnimatedSprite
{
public:
	BlackBat(int X, int Y,float vx, float vy);
	void Update(int deltaTime);
	void Draw();
	BlackBat() {};
	~BlackBat() {};
protected:
	int getAnimateRate() override { return 10; };
	string getNextFrame() override;
private:
	float velocityX;
	float velocityY;
	void updatePosition(int deltaTime);
};

