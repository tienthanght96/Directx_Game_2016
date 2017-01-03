#ifndef __MONEY_BAG_700_H__
#define __MONEY_BAG_700_H__

#define MONEY_BAG_Y 0.0975F

#define  MONEY_BAG_700 "MoneyBag700"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define MONEY_BAG_700_WIDTH 30
#define MONEY_BAG_700_HEIGHT 30
#define MONEY_BAG_700_SPRITE "Resources\\Sprites\\MoneyBag700\\MoneyBag700Sheet.png"
#define MONEY_BAG_700_SHEET "Resources\\Sprites\\MoneyBag700\\MoneyBag700Sheet"

class MoneyBag700 : public CObject, M2DXAnimatedSprite
{
public:
	MoneyBag700(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~MoneyBag700() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return MONEY_BAG_700; };
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
