#ifndef __MONEY_BAG_100_H__
#define __MONEY_BAG_100_H__

#define  MONEY_BAG_Y 0.0975F

#define  MONEY_BAG_100 "MoneyBag100"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define MONEY_BAG_100_WIDTH 30
#define MONEY_BAG_100_HEIGHT 30
#define MONEY_BAG_100_SPRITE "Resources\\Sprites\\MoneyBag100\\MoneyBag100Sheet.png"
#define MONEY_BAG_100_SHEET "Resources\\Sprites\\MoneyBag100\\MoneyBag100Sheet"

class MoneyBag100 : public CObject, M2DXAnimatedSprite
{
public:
	MoneyBag100(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~MoneyBag100() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return MONEY_BAG_100; };
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
