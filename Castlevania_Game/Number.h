#pragma once

#include "m2dxbasesprite.h"
#include "m2dxanimatedsprite.h"

#define NUMBER_SPRITE "Font\\Number\\NumberSheet.png"
#define NUMBER_SHEET "Font\\Number\\NumberSheet"


class Number : public M2DXAnimatedSprite
{
public:
	int data;
	void Update(M2DXPoint location);
	void Draw();
	Number();
	~Number() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override;
	void updateFrame();
private:
	void updatePosition(M2DXPoint location);
};

