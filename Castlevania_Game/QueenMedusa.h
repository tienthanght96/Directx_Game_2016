#ifndef __QUEEN_MEDUSA_H__
#define __QUEEN_MEDUSA_H__

#define QUEEN_MEDUSA_DEFAULT_ANIMATE_RATE 6

#define QUEEN_MEDUSA_FRAME_1 "QueenMedusaFrame1"
#define QUEEN_MEDUSA_FRAME_2 "QueenMedusaFrame2"

#define GRAVITY 0.00038828125F

#define BEFORE_DEAD_TIME 1000

#define TIME_TO_ATTACK 1300
#define TIME_TO_SHOOT 2000
#define TIME_WAITING 500

#include "SweptAABB.h"
#include "CObject.h"
#include "WeponManager.h"
#include "m2dxbasesprite.h"
#include "BulletManager.h"
#include "Snake.h"
#include "ListFlameHit.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "ItemManager.h"

#define QUEEN_MEDUSA_FLYING_SPEED 0.0425F

#define QUEEN_MEDUSA_WIDTH 64
#define QUEEN_MEDUSA_HEIGHT 64
#define QUEEN_MEDUSA_SPRITE "Resources\\Sprites\\Boss\\QueenMedusa\\QueenMedusaSheet.png"
#define QUEEN_MEDUSA_SHEET "Resources\\Sprites\\Boss\\QueenMedusa\\QueenMedusaSheet"


class QueenMedusa : public CObject, M2DXAnimatedSprite
{
	enum ActionState
	{
		attack,
		defense
	};
public:
	QueenMedusa(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	QueenMedusa() {};
	~QueenMedusa() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(QUEEN_MEDUSA_FRAME_1);
		remainingTimeToAttack = 0;
		setFlipX(true);
		velocityX = -QUEEN_MEDUSA_FLYING_SPEED;
		visible = false;
		Life = 1;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	ListFlame *beforeDead;
	void Shoot(int deltaTime);
	int remainingTimeToShoot;
	int remainingTimeWaiting;
	int remainingTimeToAttack;
	ActionState actionState;
	void updateActionState(int deltaTime);
	int Life = 1;
	float velocityX;
	float velocityY;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> listOb);
	void updateListWepon();
	void updateInfo();
	void setActionState(ActionState action) { actionState = action; };
	ActionState getActionState() { return actionState; };
	int remainingGettingDamagedTime;
	int remainingBeforDeadTime;
	void updatePosition(int deltaTime);
	void updateAD();
	void updateState(int deltaTime);
	void updateGettingDamagedTime(int deltaTime);
};

#endif
