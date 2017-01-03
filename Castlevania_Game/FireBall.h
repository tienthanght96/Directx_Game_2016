#ifndef __FIRE_BALL_H__
#define __FIRE_BALL_H__

#define VELOCITY_X 0.0975F

#define FIRE_BALL "FireBall"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"

#define FIRE_BALL_WIDTH 14
#define FIRE_BALL_HEIGHT 12
#define FIRE_BALL_SPRITE "Resources\\Sprites\\BulletFromEnemy\\FireBall\\FireBallSheet.png"
#define FIRE_BALL_SHEET "Resources\\Sprites\\BulletFromEnemy\\FireBall\\FireBallSheet"

class FireBall : public CObject, M2DXAnimatedSprite
{
public:
	FireBall(int X, int Y, AttackDirection direc);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~FireBall() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override { return FIRE_BALL; };
private:
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
