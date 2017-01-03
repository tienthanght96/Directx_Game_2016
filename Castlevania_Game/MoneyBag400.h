#ifndef __MONEY_BAG_400_H__
#define __MONEY_BAG_400_H__

#define MONEY_BAG_Y 0.0975F

#define  MONEY_BAG_400 "MoneyBag400"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define MONEY_BAG_400_WIDTH 32
#define MONEY_BAG_400_HEIGHT 30
#define MONEY_BAG_400_SPRITE "Resources\\Sprites\\MoneyBag400\\MoneyBag400Sheet.png"
#define MONEY_BAG_400_SHEET "Resources\\Sprites\\MoneyBag400\\MoneyBag400Sheet"

class MoneyBag400 : public CObject, M2DXAnimatedSprite
{
public:
	MoneyBag400(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~MoneyBag400() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return MONEY_BAG_400; };
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
