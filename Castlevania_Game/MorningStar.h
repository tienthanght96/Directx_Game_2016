#ifndef __MORNING_STAR_H__
#define __MORNING_STAR_H__

#define  MORNING_STAR_Y 0.0975F

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define MORNING_STAR_WIDTH 30
#define MORNING_STAR_HEIGHT 30
#define MORNING_STAR_SPRITE "Resources\\Sprites\\WeaponsItem\\MorningStar.png"

class MorningStar : public CObject, M2DXBaseSprite
{
public:
	MorningStar(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~MorningStar() {};
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
