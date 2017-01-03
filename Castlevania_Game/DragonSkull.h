#ifndef __DRAGON_SKULL_H__
#define __DRAGON_SKULL_H__

#define DRAGON_SKULL_DEFAULT_ANIMATE_RATE 6

#define DRAGON_SKULL "DragonSkull"
#define BEFORE_DEAD "BeforeDead"

#define TIME_TO_SHOOT 800

#define DRAGON_SKULL_BEFORE_DEAD_TIME 300

#include "SweptAABB.h"
#include "CObject.h"
#include "WeponManager.h"
#include "m2dxbasesprite.h"
#include "BulletManager.h"
#include "Fireball.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "ItemManager.h"

#define DRAGON_SKULL_WIDTH 34
#define DRAGON_SKULL_HEIGHT 64
#define DRAGON_SKULL_SPRITE "Resources\\Sprites\\DragonSkull\\DragonSkullSheet.png"
#define DRAGON_SKULL_SHEET "Resources\\Sprites\\DragonSkull\\DragonSkullSheet"


class DragonSkull : public CObject, M2DXAnimatedSprite
{
public:
	DragonSkull(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	DragonSkull() {};
	~DragonSkull() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(DRAGON_SKULL);
		remainingTimeToShoot = 0;
		health = 400;
	};
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	int health = 400;
	int dem = 2;
	D3DXCOLOR color;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> listOb);
	void updateListWepon();
	bool canShoot = true;
	int remainingTimeToShoot;
	void Shoot(int deltaTime);
	void updateAD();
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
