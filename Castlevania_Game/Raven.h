#ifndef __RAVEN_H__
#define __RAVEN_H__

#define RAVEN_DEFAULT_ANIMATE_RATE 10

#define RAVEN_SITTING "RavenSitting"
#define RAVEN_FRAME_1 "RavenFrame1"
#define RAVEN_FRAME_2 "RavenFrame2"
#define RAVEN_FRAME_3 "RavenFrame3"
#define RAVEN_FRAME_4 "RavenFrame4"
#define BEFORE_DEAD "BeforeDead"

#define BEFORE_DEAD_TIME 300
#define FLY_TIME 1000
#define SITTING_TIME 500

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

#define RAVEN_FLYING_SPEED 0.0225F

#define RAVEN_WIDTH 32
#define RAVEN_HEIGHT 24
#define RAVEN_SPRITE "Resources\\Sprites\\Raven\\RavenSheet.png"
#define RAVEN_SHEET "Resources\\Sprites\\Raven\\RavenSheet"


class Raven : public CObject, M2DXAnimatedSprite
{
	enum ActionState
	{
		Flying,
		Sitting
	};
public:
	Raven(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	Raven() {};
	~Raven() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(RAVEN_SITTING);
		setFlipX(true);
		velocityX = -RAVEN_FLYING_SPEED;
		currentActionState = ActionState::Sitting;
		Life = 1;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	ActionState currentActionState;
	void updateActionState(int deltaTime);
	int remainingFly = FLY_TIME;
	int remainingSitting = SITTING_TIME;
	int Life = 1;
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
