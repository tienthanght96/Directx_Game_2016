#include "FlameHit.h"

FlameHit::FlameHit(int X, int Y, int item) : CObject(18, X, Y, FLAME_HIT_WIDTH, FLAME_HIT_HEIGHT, item)
{
	initWithTexture(FLAME_HIT_SHEET);
	setCurrentFrame(FLAME_HIT_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void FlameHit::Update(int DeltaTime)
{
	updateFrame(DeltaTime);
}


void FlameHit::Draw()
{
	M2DXAnimatedSprite::draw();
}

int FlameHit::getAnimateRate()
{
	return FLAME_HIT_DEFAULT_ANIMATE_RATE;
}

string FlameHit::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	if (currentFrame == FLAME_HIT_FRAME_1)
		return FLAME_HIT_FRAME_2;
	if (currentFrame == FLAME_HIT_FRAME_2)
		return FLAME_HIT_FRAME_3;
	if (currentFrame == FLAME_HIT_FRAME_3)
		return FLAME_HIT_FRAME_4;
	if (currentFrame == FLAME_HIT_FRAME_4)
		return FLAME_HIT_FRAME_1;
}


