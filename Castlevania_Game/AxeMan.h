#ifndef __AXE_MAN_H__
#define __AXE_MAN_H__

#define AXE_MAN_DEFAULT_ANIMATE_RATE 3

#define AXE_MAN_FRAME_1 "AxeManFrame1"
#define AXE_MAN_FRAME_2 "AxeManFrame2"
#define BEFORE_DEAD "BeforeDead"

#define GRAVITY 0.00048828125F

#define BEFORE_DEAD_TIME 300

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "WeponManager.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "ItemManager.h"

#define AXE_MAN_WALKING_SPEED 0.0325F

#define AXE_MAN_WIDTH 48
#define AXE_MAN_HEIGHT 64
#define AXE_MAN_SPRITE "Resources\\Sprites\\AxeMan\\AxeManSheet.png"
#define AXE_MAN_SHEET "Resources\\Sprites\\AxeMan\\AxeManSheet"


class AxeMan : public CObject, M2DXAnimatedSprite
{
public:
	AxeMan(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	AxeMan() {};
	~AxeMan() {};
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	int Life = 5;
	float velocityX;
	float velocityY;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> list);
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
