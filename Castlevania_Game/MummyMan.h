#ifndef __MUMMY_MAN_H__
#define __MUMMY_MAN_H__

#define MUMMY_MAN_DEFAULT_ANIMATE_RATE 6

#define MUMMY_MAN_FRAME_1 "MummyManFrame1"
#define MUMMY_MAN_FRAME_2 "MummyManFrame2"
#define MUMMY_MAN_FRAME_3 "MummyManFrame3"
#define MUMMY_MAN_FRAME_4 "MummyManFrame4"

#define GRAVITY 0.00048828125F

#define BEFORE_DEAD_TIME 1000
#define TIME_TO_SHOOT 1500
#define TIME_WAITING 500

#include "SweptAABB.h"
#include "CObject.h"
#include "WeponManager.h"
#include "BulletManager.h"
#include "ListFlameHit.h"
#include "BloodManager.h"
#include "Bandage.h"
#include "m2dxbasesprite.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "ItemManager.h"

#define MUMMY_MAN_WALKING_SPEED 0.0325F

#define MUMMY_MAN_WIDTH 32
#define MUMMY_MAN_HEIGHT 80
#define MUMMY_MAN_SPRITE "Resources\\Sprites\\Boss\\MummyMan\\MummyManSheet.png"
#define MUMMY_MAN_SHEET "Resources\\Sprites\\Boss\\MummyMan\\MummyManSheet"


class MummyMan : public CObject, M2DXAnimatedSprite
{
public:
	MummyMan(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	MummyMan() {};
	~MummyMan() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(MUMMY_MAN_FRAME_1);
		setFlipX(true);
		velocityX = -MUMMY_MAN_WALKING_SPEED;
		visible = false;
		Life = 2;
		
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	D3DXCOLOR color;
	int remainingChangeColor = 2;
	void changeColor();
	int R, G, B;
	ListFlame *beforeDead;
	int remainingTimeWaiting;
	int remainingTimeToShoot;
	bool goMid = true;
	int MidScreen;
	int dem = 0;
	void Shoot(int deltaTime);
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
