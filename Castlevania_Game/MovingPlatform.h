#ifndef __MOVING_PLATFORM_H__
#define __MOVING_PLATFORM_H__

#define MOVING_PLATFORM "MovingPlatform"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"

#define MOVING_PLATFORM_SPEED 0.0325F

#define PLATFORM_WIDTH 64
#define PLATFORM_HEIGHT 16
#define PLATFORM_SPRITE "Resources\\Sprites\\MovingPlatform\\MovingPlatformSheet.png"
#define PLATFORM_SHEET "Resources\\Sprites\\MovingPlatform\\MovingPlatformSheet"


class MovingPlatform : public CObject, M2DXAnimatedSprite
{
public:
	MovingPlatform(int X, int Y, int item);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	MovingPlatform() {};
	~MovingPlatform() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return MOVING_PLATFORM; };
private:
	void updateInfor(int deltaTime);
	void updatePosition(int deltaTime);
};

#endif
