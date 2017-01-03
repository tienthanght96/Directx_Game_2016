#ifndef __GHOST_H__
#define __GHOST_H__

#define GHOST_DEFAULT_ANIMATE_RATE 6

#define GHOST_FRAME_1 "GhostFrame1"
#define GHOST_FRAME_2 "GhostFrame2"
#define BEFORE_DEAD "BeforeDead"

#define GRAVITY 0.00038828125F

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

#define GHOST_FLYING_SPEED 0.0225F

#define GHOST_WIDTH 32
#define GHOST_HEIGHT 32
#define GHOST_SPRITE "Resources\\Sprites\\Ghost\\GhostSheet.png"
#define GHOST_SHEET "Resources\\Sprites\\Ghost\\GhostSheet"


class Ghost : public CObject, M2DXAnimatedSprite
{
public:
	Ghost(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	Ghost() {};
	~Ghost() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(GHOST_FRAME_1);
		setFlipX(true);
		velocityX = -GHOST_FLYING_SPEED;
		setState(State::alive);
		Life = 2;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	bool inRange = false;
	int Life = 2;
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
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updatePosition(int deltaTime);
	void updateAD();
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
