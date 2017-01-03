#ifndef __HUNCHBACK_H__
#define __HUNCHBACK_H__

#define HUNCHBACK_DEFAULT_ANIMATE_RATE 8

#define HUNCHBACK_FRAME_1 "HunchbackFrame1"
#define HUNCHBACK_FRAME_2 "HunchbackFrame2"
#define BEFORE_DEAD "BeforeDead"

#define GRAVITY 0.00038828125F

#define BEFORE_DEAD_TIME 500

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

#define HUNCHBACK_WALKING_SPEED 0.0625F
#define HUNCHBACK_JUMPING_SPEED -0.1875F

#define HUNCHBACK_WIDTH 32
#define HUNCHBACK_HEIGHT 32
#define HUNCHBACK_SPRITE "Resources\\Sprites\\Hunchback\\HunchbackSheet.png"
#define HUNCHBACK_SHEET "Resources\\Sprites\\Hunchback\\HunchbackSheet"


class Hunchback : public CObject, M2DXAnimatedSprite
{
public:
	Hunchback(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	Hunchback() {};
	~Hunchback() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(HUNCHBACK_FRAME_1);
		setFlipX(true);
		velocityX = HUNCHBACK_WALKING_SPEED;
		Life = 1;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	bool isJumping = false;
	bool isJumpHight = true;
	bool canChangeDirec = true;
	int Life = 1;
	int dem = 0;
	int Left = 1;
	int Right = 1;
	float velocityX;
	float velocityY;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> listOb);
	void updateListWepon();
	void updateInfo();
	int remainingJump = 1500;
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updatePosition(int deltaTime);
	void updateAD();
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
