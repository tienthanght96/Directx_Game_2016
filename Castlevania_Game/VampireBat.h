#ifndef __VAMPIRE_BAT_H__
#define __VAMPIRE_BAT_H__

#define VAMPIRE_BAT_DEFAULT_ANIMATE_RATE 6

#define VAMPIRE_BAT_FRAME_1 "VampireBatFrame1"
#define VAMPIRE_BAT_FRAME_2 "VampireBatFrame2"
#define VAMPIRE_BAT_FRAME_3 "VampireBatFrame3"
#define VAMPIRE_BAT_FRAME_4 "VampireBatFrame4"
#define VAMPIRE_BAT_HANGING "VampireBatHanging"
#define BEFORE_DEAD "BeforeDead"

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

#define VAMPIRE_BAT_FLYING_SPEED 0.1025F

#define VAMPIRE_BAT_WIDTH 24
#define VAMPIRE_BAT_HEIGHT 28
#define VAMPIRE_BAT_SPRITE "Resources\\Sprites\\VampireBat\\VampireBatSheet.png"
#define VAMPIRE_BAT_SHEET "Resources\\Sprites\\VampireBat\\VampireBatSheet"


class VampireBat : public CObject, M2DXAnimatedSprite
{
	enum ActionState
	{
		Hanging,
		Flying
	};
public:
	VampireBat(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	VampireBat() {};
	~VampireBat() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setActionState(Hanging);
		setCurrentFrame(VAMPIRE_BAT_HANGING);
		velocityX = 0;
		velocityY = 0;
		Life = 1;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	ActionState actionState;
	void setActionState(ActionState action) { actionState = action; };
	ActionState getActionState() { return actionState; };
	void updateActionState();
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
