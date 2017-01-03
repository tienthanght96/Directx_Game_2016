#ifndef __WHITE_SKELETON_H__
#define __WHITE_SKELETON_H__

#define WHITE_SKELETON_DEFAULT_ANIMATE_RATE 6

#define WHITE_SKELETON_FRAME_1 "WhiteSkeletonFrame1"
#define WHITE_SKELETON_FRAME_2 "WhiteSkeletonFrame2"
#define BEFORE_DEAD "BeforeDead"

#define GRAVITY 0.00038828125F

#define BEFORE_DEAD_TIME 400

#define TIME_TO_ATTACK 1300
#define TIME_TO_SHOOT 300
#define TIME_WAITING 500

#include "SweptAABB.h"
#include "CObject.h"
#include "WeponManager.h"
#include "m2dxbasesprite.h"
#include "BulletManager.h"
#include "WhiteBone.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "ItemManager.h"

#define WHITE_SKELETON_WALKING_SPEED 0.0625F
#define WHITE_SKELETON_JUMPING_SPEED 0.1975F

#define WHITE_SKELETON_WIDTH 32
#define WHITE_SKELETON_HEIGHT 64
#define WHITE_SKELETON_SPRITE "Resources\\Sprites\\WhiteSkeleton\\WhiteSkeletonSheet.png"
#define WHITE_SKELETON_SHEET "Resources\\Sprites\\WhiteSkeleton\\WhiteSkeletonSheet"


class WhiteSkeleton : public CObject, M2DXAnimatedSprite
{
public:
	WhiteSkeleton(int X, int Y, int item);
	M2DXBaseSprite gettingDamaged;
	bool getDamaged = false;
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	WhiteSkeleton() {};
	~WhiteSkeleton() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		setCurrentFrame(WHITE_SKELETON_FRAME_1);
		setFlipX(true);
		velocityY = 0;
	}
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
private:
	void Shoot(int deltaTime);
	bool inRange();
	bool isShooting = false;
	int remainingTimeToShoot = 0;
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
