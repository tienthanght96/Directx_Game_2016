#include "BatScreen.h"

BatScreen::BatScreen(int X, int Y)
{
	initWithTexture(BAT_SHEET);
	setFlipX(false);
	setPosition(M2DXPoint(X,Y));
	currentState = Begin;
	setCurrentFrame(BAT_FRAME_1);
}

void BatScreen::Update(int deltaTime)
{
	updateState();

	updateFrame(deltaTime);
}

void BatScreen::Draw()
{
	M2DXBaseSprite::draw();
}

string BatScreen::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (currentState)
	{
	case Begin:
		if (currentFrame == BAT_FRAME_1)
			return BAT_FRAME_2;
		if (currentFrame == BAT_FRAME_2)
			return BAT_FRAME_3;
		if (currentFrame == BAT_FRAME_3)
			return BAT_FRAME_4;
		if (currentFrame == BAT_FRAME_4)
			return BAT_FRAME_5;
		if (currentFrame == BAT_FRAME_5)
			return BAT_FRAME_6;
		if (currentFrame == BAT_FRAME_6)
			return BAT_FRAME_7;
		if (currentFrame == BAT_FRAME_7)
			return BAT_FRAME_8;
		if (currentFrame == BAT_FRAME_8)
			return BAT_FRAME_9;
		if (currentFrame == BAT_FRAME_9)
			return BAT_FRAME_10;
		if (currentFrame == BAT_FRAME_10)
			return BAT_FRAME_11;
		if (currentFrame == BAT_FRAME_11)
			return BAT_FRAME_12;
		break;
	case End:
		if (currentFrame == BAT_FRAME_12)
			return BAT_FRAME_13;
		if (currentFrame == BAT_FRAME_13)
			return BAT_FRAME_14;
		if (currentFrame == BAT_FRAME_14)
			return BAT_FRAME_15;
		if (currentFrame == BAT_FRAME_15)
			return BAT_FRAME_13;
		break;
	}
}

void BatScreen::updateState()
{
	if (getCurrentFrame() == BAT_FRAME_12)
		currentState = End;
}
