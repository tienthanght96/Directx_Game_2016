#include "BloodSimon.h"

BloodSimon::BloodSimon(string nameOb)
{
	if (nameOb == "Simon")
	initWithTexture(BLOOD_SIMON_SHEET);
	else
		if(nameOb == "Enemy")
			initWithTexture(BLOOD_ENEMY_SHEET);
	state = "Full";
}

void BloodSimon::Update(M2DXPoint location)
{
	updatePosition(location);

	updateFrame();
}

void BloodSimon::Draw()
{
	M2DXBaseSprite::draw();
}

string BloodSimon::getNextFrame()
{
	return state;
}

void BloodSimon::updateFrame()
{
	setCurrentFrame(getNextFrame());
}

void BloodSimon::updatePosition(M2DXPoint location)
{
	setPosition(location);
}
