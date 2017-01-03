#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#define ZOMBIE_DEFAULT_ANIMATE_RATE 6

#define ZOMBIE_FRAME_1 "ZombieFrame1"
#define ZOMBIE_FRAME_2 "ZombieFrame2"
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

#define ZOMBIE_WALKING_SPEED 0.0625F

#define ZOMBIE_WIDTH 32
#define ZOMBIE_HEIGHT 64
#define ZOMBIE_SPRITE "Resources\\Sprites\\Zombie\\Zombie.png"
#define ZOMBIE_SHEET "Resources\\Sprites\\Zombie\\Zombie"


class Zombie : public CObject, M2DXAnimatedSprite
{
public:
	Zombie(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	Zombie() {};
	~Zombie() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(ZOMBIE_FRAME_1);
		setFlipX(true);
		velocityX = -ZOMBIE_WALKING_SPEED;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	float velocityX;
	float velocityY;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> listOb);
	void updateListWepon();
	void updateInfo();
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updatePosition(int deltaTime);
	void updateAD();
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
