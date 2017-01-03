#include "Wepon.h"



Wepon::Wepon()
{
	initWithTexture(WEPON_SHEET);
	state = "Axe";
}

void Wepon::Update(M2DXPoint location)
{
	updatePosition(location);

	updateFrame();
}

void Wepon::Draw()
{
	M2DXBaseSprite::draw();
}

string Wepon::getNextFrame()
{
	return state;
}

void Wepon::updateFrame()
{
	setCurrentFrame(getNextFrame());
}

void Wepon::updatePosition(M2DXPoint location)
{
	setPosition(location);
}
