#ifndef __LARGECANDLE_H__
#define __LARGECANDLE_H__

#define LARGE_CANDLE_DEFAULT_ANIMATE_RATE 6

#define LARGE_CANDLE_FRAME_BEGIN "LargeCandleBegin"
#define LARGE_CANDLE_FRAME_END "LargeCandleEnd"
#define LARGE_CANDLE_FRAME_BEFOR_DEAD "BeforeDead"

#define LARGE_CANDLE_BEFORE_DEAD_TIME 300

#include "SweptAABB.h"
#include "CObject.h"
#include "WeponManager.h"
#include "m2dxbasesprite.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "Potion.h"
#include "Cross.h"
#include "MorningStar.h"
#include "ItemManager.h"

#define CANDLE_WIDTH 16
#define CANDLE_HEIGHT 32
#define CANDLE_SPRITE "Resources\\Sprites\\LargeCandle\\LargeCandle.png"
#define CANDLE_SHEET "Resources\\Sprites\\LargeCandle\\LargeCandle"


class Candle : public CObject, M2DXAnimatedSprite
{
public:
	Candle(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob) ;
	void Draw();
	Candle();
	~Candle();
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(LARGE_CANDLE_FRAME_BEGIN);
		health = 50;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	int health = 50;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> listOb);
	void updateListWepon();
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
