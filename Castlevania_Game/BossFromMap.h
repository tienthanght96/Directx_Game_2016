#pragma once

#include "m2dxbasesprite.h"
#include "m2dxanimatedsprite.h"

#define BAT_FRAME_1 "BossFromMapFrame1"
#define BAT_FRAME_2 "BossFromMapFrame2"


#define BAT_SHEET "Map\\BossFromMapSheet"


class BossFromMap : public M2DXAnimatedSprite
{
public:
	BossFromMap(int X, int Y);
	void Update(int deltaTime);
	void Draw();
	BossFromMap() {};
	~BossFromMap() {};
protected:
	int getAnimateRate() override { return 10; };
	string getNextFrame() override;

};

