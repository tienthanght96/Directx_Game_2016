#ifndef __LARGE_HEART_H__
#define __LARGE_HEART_H__

#define LARGE_HEART_Y 0.0975F

#define LARGE_HEART "LargeHeart"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define LARGE_HEART_WIDTH 26
#define LARGE_HEART_HEIGHT 20
#define LARGE_HEART_SPRITE "Resources\\Sprites\\LargeHeart\\LargeHeartSheet.png"
#define LARGE_HEART_SHEET "Resources\\Sprites\\LargeHeart\\LargeHeartSheet"

class LargeHeart : public CObject, M2DXAnimatedSprite
{
public:
	LargeHeart(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~LargeHeart() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return LARGE_HEART; };
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
