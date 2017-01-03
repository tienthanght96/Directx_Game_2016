#include "BossFromMap.h"

BossFromMap::BossFromMap(int X, int Y)
{
	initWithTexture(BAT_SHEET);
	setFlipX(false);
	setPosition(M2DXPoint(X,Y));
	setCurrentFrame(BAT_FRAME_1);
}

void BossFromMap::Update(int deltaTime)
{
	updateFrame(deltaTime);
}

void BossFromMap::Draw()
{
	M2DXBaseSprite::draw();
}

string BossFromMap::getNextFrame()
{
	if (getCurrentFrame() == BAT_FRAME_1)
		return BAT_FRAME_2;
	else
		return BAT_FRAME_1;
}
