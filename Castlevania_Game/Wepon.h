#pragma once

#include "m2dxbasesprite.h"
#include "m2dxanimatedsprite.h"

#define WEPON_SPRITE "Font\\Wepon\\WeponsSheet.png"
#define WEPON_SHEET "Font\\Wepon\\WeponsSheet"


class Wepon : public M2DXAnimatedSprite
{
public:
	string state;
	void setWeponState(string bloodState) { state = bloodState; };
	void Update(M2DXPoint location);
	void Draw();
	Wepon();
	~Wepon() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override;
	void updateFrame();
private:
	void updatePosition(M2DXPoint location);
};

