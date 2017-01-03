#include "BatIntro.h"

BlackBat::BlackBat(int X, int Y, float vx, float vy)
{
	initWithTexture(BAT_SHEET);
	setFlipX(false);
	setPosition(M2DXPoint(X,Y));
	velocityX = vx;
	velocityY = vy;
}

void BlackBat::Update(int deltaTime)
{
	updateFrame(deltaTime);

	updatePosition(deltaTime);
}

void BlackBat::Draw()
{
	M2DXBaseSprite::draw();
}

string BlackBat::getNextFrame()
{
	auto curentFrame = getCurrentFrame();
	if (curentFrame == BAT_FRAME_1)
		return BAT_FRAME_2;
	else
		return BAT_FRAME_1;
}

void BlackBat::updatePosition(int deltaTime)
{
	auto position = getPosition();
	position.x += velocityX*deltaTime;
	position.y += velocityY*deltaTime;
	if (getCurrentFrame() == BAT_FRAME_1)
		position.y += 1;
	else
		position.y -= 1;
	setPosition(position);
}
