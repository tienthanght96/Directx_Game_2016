#ifndef __SMALL_HEART_H__
#define __SMALL_HEART_H__

#define SMALL_HEART_Y 0.0475F
#define SMALL_HEART_X 0.0675F
#define GRAVITY 0.00038828125F

#define SMALL_HEART "SmallHeart"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#include "Heart.h"

#define SMALL_HEART_WIDTH 16
#define SMALL_HEART_HEIGHT 16
#define SMALL_HEART_SPRITE "Resources\\Sprites\\SmallHeart\\SmallHeartSheet.png"
#define SMALL_HEART_SHEET "Resources\\Sprites\\SmallHeart\\SmallHeartSheet"

class SmallHeart : public CObject, M2DXAnimatedSprite
{
public:
	SmallHeart(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~SmallHeart() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return SMALL_HEART; };
private:
	float gravity;
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
