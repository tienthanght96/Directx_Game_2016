#ifndef __MEDUSA_H__
#define __MEDUSA_H__

#define MEDUSA_DEFAULT_ANIMATE_RATE 6

#define MEDUSA_FRAME_1 "MedusaFrame1"
#define MEDUSA_FRAME_2 "MedusaFrame2"
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

#define MEDUSA_FLYING_SPEED 0.0625F
#define MEDUSA_JUMPING_SPEED - 0.1175F

#define MEDUSA_WIDTH 32
#define MEDUSA_HEIGHT 32
#define MEDUSA_SPRITE "Resources\\Sprites\\Medusa\\MedusaSheet.png"
#define MEDUSA_SHEET "Resources\\Sprites\\Medusa\\MedusaSheet"


class Medusa : public CObject, M2DXAnimatedSprite
{
public:
	Medusa(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	Medusa() {};
	~Medusa() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(MEDUSA_FRAME_1);
		setFlipX(true);
		gravity = GRAVITY;
		velocityX = -MEDUSA_FLYING_SPEED;
		velocityY = MEDUSA_JUMPING_SPEED;
		setState(State::alive);
		Life = 1;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	float gravity;
	int Life = 1;
	int defaultX;
	int defaultY;
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
