#pragma once

#include "m2dxbasesprite.h"
#define SPRITE_SHEET_INFORMATION_FILE_EXTENSION ".txt"
#include <map>

typedef pair<string, M2DXRectangle> M2DXFramePair;

class M2DXAnimatedSprite : public virtual M2DXBaseSprite
{
public:
	M2DXAnimatedSprite();
	~M2DXAnimatedSprite();

	bool initWithTexture(LPCSTR textureName) override;

	virtual M2DXSize getSize();

protected:
	inline string getCurrentFrame() { return currentFrame; }
	inline void setCurrentFrame(string currentFrame) { this->currentFrame = currentFrame; }


	void updateFrame(int deltaTime);

	virtual int getAnimateRate() = 0;

	virtual string getNextFrame(); // Override this method in derived class to decide frame to render.

	RECT getSourceRectangle() override;

private:
	std::map<string, M2DXRectangle> frameMap;

	string currentFrame;
	string nextFrame;
	int frameTime;

	M2DXSize getCurrentFrameSize();

	inline void switchFrame() { currentFrame = nextFrame; }
};
