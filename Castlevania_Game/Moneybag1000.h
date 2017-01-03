#ifndef __MONEY_BAG_1000_H__
#define __MONEY_BAG_1000_H__

#define MONEY_BAG_Y 0.0975F

#define MONEY_BAG_DEFAULT_RATE 10

#define  MONEY_BAG_FRAME_1 "MoneyBagFrame1"
#define  MONEY_BAG_FRAME_2 "MoneyBagFrame2"
#define  MONEY_BAG_FRAME_3 "MoneyBagFrame3"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"

#define MONEY_BAG_1000_WIDTH 30
#define MONEY_BAG_1000_HEIGHT 30
#define MONEY_BAG_1000_SPRITE "Resources\\Sprites\\MoneyBag1000\\MoneyBag1000.png"
#define MONEY_BAG_1000_SHEET "Resources\\Sprites\\MoneyBag1000\\MoneyBag1000"

class MoneyBag1000 : public CObject, M2DXAnimatedSprite
{
public:
	MoneyBag1000(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~MoneyBag1000() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override ;
private:
	int remainingVisible = 5000;
	void updateVisible(int DeltaTime);
	int positionY;
	void updateFrame();
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
