#include "m2dxanimatedsprite.h"

M2DXAnimatedSprite::M2DXAnimatedSprite() { }

M2DXAnimatedSprite::~M2DXAnimatedSprite() { }

bool M2DXAnimatedSprite::initWithTexture(LPCSTR textureName)
{
	setTexture(M2DXResourceManager::getInstance()->getTextureByName(textureName));
	if (!getTexture())
	{
		return false;
	}

	auto informationFileName = (string)textureName + SPRITE_SHEET_INFORMATION_FILE_EXTENSION;

	ifstream informationFile(informationFileName);
	if (informationFile.is_open())
	{
		string frameInformation;
		while (getline(informationFile, frameInformation))
		{
			auto frameNameSize = frameInformation.find_last_of("=") - 1; // {Name} = {Rect}. Examples: SimonBelmont = 0 0 16 32
			auto frameName = frameInformation.substr(0, frameNameSize);

			auto rectangleInformation = frameInformation.substr(frameNameSize + 3);
			stringstream stringStream(rectangleInformation);
			float x, y, width, height;
			stringStream >> x;
			stringStream >> y;
			stringStream >> width;
			stringStream >> height;
			M2DXRectangle frameRectangle(x, y, width, height);

			frameMap.insert(M2DXFramePair(frameName, frameRectangle));
		}

		currentFrame = frameMap.begin()->first;
		frameTime = getAnimateRate();
	}

	return false;
}

void M2DXAnimatedSprite::updateFrame(int deltaTime)
{
	auto animateRate = getAnimateRate();
	if (animateRate != 0)
	{
		if (getNextFrame() == "SimonBelmontKneeling" || getNextFrame() == "SimonBelmontStanding" || getNextFrame() =="SimonBelmontOnKneelAttackingBegin")
		{
			nextFrame = getNextFrame();
			switchFrame();
		}
		else
		{
			frameTime -= deltaTime;
			if (frameTime <= 0)
			{
				frameTime = 1000 / animateRate;
				nextFrame = getNextFrame();
				switchFrame();
			}
		}
	}
}

string M2DXAnimatedSprite::getNextFrame()
{
	auto iterator = frameMap.find(currentFrame);
	if (iterator != frameMap.end())
	{
		iterator++;
	}
	else
	{
		iterator == frameMap.begin();
	}

	return iterator->first;
}

RECT M2DXAnimatedSprite::getSourceRectangle()
{
	auto frameRectangle = frameMap[currentFrame];

	RECT sourceRectangle;
	sourceRectangle.left = frameRectangle.left;
	sourceRectangle.top = frameRectangle.top;
	sourceRectangle.right = frameRectangle.right;
	sourceRectangle.bottom = frameRectangle.bottom;

	return sourceRectangle;
}

M2DXSize M2DXAnimatedSprite::getSize()
{
	return getCurrentFrameSize();
}

M2DXSize M2DXAnimatedSprite::getCurrentFrameSize()
{
	auto currentFrameRectangle = frameMap[currentFrame];

	return M2DXSize(currentFrameRectangle.right - currentFrameRectangle.left, currentFrameRectangle.bottom - currentFrameRectangle.top);
}
