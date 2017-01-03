#ifndef __WHITE_BONE_H__
#define __WHITE_BONE_H__

#define WHITEBONE_X 0.0425F
#define WHITEBONE_Y -0.2075F

#define WHITE_BONE_DEFAULT_ANIMATE_RATE 6

#define WHITE_BONE_FRAME_1 "WhiteBoneFrame1"
#define WHITE_BONE_FRAME_2 "WhiteBoneFrame2"
#define WHITE_BONE_FRAME_3 "WhiteBoneFrame3"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"

#define WHITE_BONE_WIDTH 30
#define WHITE_BONE_HEIGHT 32
#define WHITE_BONE_SPRITE "Resources\\Sprites\\BulletFromEnemy\\WhiteBone\\WhiteBoneSheet.png"
#define WHITE_BONE_SHEET "Resources\\Sprites\\BulletFromEnemy\\WhiteBone\\WhiteBoneSheet"

class WhiteBone : public CObject, M2DXAnimatedSprite
{
public:
	WhiteBone(int X, int Y, AttackDirection direc);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~WhiteBone() {};
protected:
	int getAnimateRate() override { return WHITE_BONE_DEFAULT_ANIMATE_RATE; };
	string getNextFrame() override;
private:
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
