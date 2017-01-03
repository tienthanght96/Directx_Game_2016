#ifndef __BANDAGE_H__
#define __BANDAGE_H__

#define BANDAGE_X 0.0675F
#define BANDAGE_Y 0.1175F

#define SNAKE_DEFAULT_ANIMATE_RATE 6

#define BANDAGE_FRAME_1 "BandageFrame1"
#define BANDAGE_FRAME_2 "BandageFrame2"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"


#define BANDAGE_WIDTH 32
#define BANDAGE_HEIGHT 18
#define BANDAGE_SPRITE "Resources\\Sprites\\BulletFromEnemy\\Bandage\\BandageSheet.png"
#define BANDAGE_SHEET "Resources\\Sprites\\BulletFromEnemy\\Bandage\\BandageSheet"

class Bandage : public CObject, M2DXAnimatedSprite
{
public:
	Bandage(int X, int Y, AttackDirection direc);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~Bandage() {};
protected:
	int getAnimateRate() override { return SNAKE_DEFAULT_ANIMATE_RATE; };
	string getNextFrame() override;
private:
	float gravity;
	float defaultY;
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
