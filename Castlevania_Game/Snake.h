#ifndef __SNAKE_H__
#define __SNAKE_H__

#define VELOCITY_X 0.0975F

#define SNAKE_DEFAULT_ANIMATE_RATE 6

#define SNAKE_FRAME_1 "SnakeFrame1"
#define SNAKE_FRAME_2 "SnakeFrame2"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"

#define SNAKE_WIDTH 32
#define SNAKE_HEIGHT 20
#define SNAKE_SPRITE "Resources\\Sprites\\BulletFromEnemy\\Snake\\SnakeSheet.png"
#define SNAKE_SHEET "Resources\\Sprites\\BulletFromEnemy\\Snake\\SnakeSheet"

class Snake : public CObject, M2DXAnimatedSprite
{
public:
	Snake(int X, int Y, AttackDirection direc);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~Snake() {};
protected:
	int getAnimateRate() override { return SNAKE_DEFAULT_ANIMATE_RATE; };
	string getNextFrame() override ;
private:
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
