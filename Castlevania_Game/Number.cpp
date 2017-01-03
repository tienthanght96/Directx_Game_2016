#include "Number.h"

Number::Number()
{
	initWithTexture(NUMBER_SHEET);
	this->data = data;
}

void Number::Update(M2DXPoint location)
{
	updatePosition(location);

	updateFrame();
}

void Number::Draw()
{
	M2DXBaseSprite::draw();
}

string Number::getNextFrame()
{
	switch (data)
	{
	case 0:
		return "0";
		break;
	case 1:
		return "1";
		break;
	case 2:
		return "2";
		break;
	case 3:
		return "3";
		break;
	case 4:
		return "4";
		break;
	case 5:
		return "5";
		break;
	case 6:
		return "6";
		break;
	case 7:
		return "7";
		break;
	case 8:
		return "8";
		break;
	case 9:
		return "9";
		break;
	}
}

void Number::updateFrame()
{
		setCurrentFrame(getNextFrame());
}

void Number::updatePosition(M2DXPoint location)
{
	setPosition(location);
}
