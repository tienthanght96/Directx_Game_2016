#ifndef __BLACK_KNIGHT_H__
#define __BLACK_KNIGHT_H__

#define BLACK_KNIGHT_DEFAULT_ANIMATE_RATE 6

#define BLACK_KNIGHT_FRAME_1 "BlackKnightFrame1"
#define BLACK_KNIGHT_FRAME_2 "BlackKnightFrame2"
#define BLACK_KNIGHT_FRAME_3 "BlackKnightFrame3"
#define BLACK_KNIGHT_FRAME_4 "BlackKnightFrame4"
#define BEFORE_DEAD "BeforeDead"

#define GRAVITY 0.00048828125F

#define BEFORE_DEAD_TIME 300

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
#include "ItemManager.h"

#define BLACK_KNIGHT_WALKING_SPEED 0.0325F

#define BLACK_KNIGHT_WIDTH 32
#define BLACK_KNIGHT_HEIGHT 64
#define BLACK_KNIGHT_SPRITE "Resources\\Sprites\\BlackKnight\\BlackKnightSheet.png"
#define BLACK_KNIGHT_SHEET "Resources\\Sprites\\BlackKnight\\BlackKnightSheet"


class BlackKnight : public CObject, M2DXAnimatedSprite
{
public:
	BlackKnight(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	void Restore();
	BlackKnight() {};
	~BlackKnight() {};
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	int Life = 2;
	float velocityX;
	float velocityY;
	void updateInfo();
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> list);
	void updateListWepon();
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updatePosition(int deltaTime);
	void updateAD();
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
