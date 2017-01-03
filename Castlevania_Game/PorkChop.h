#ifndef __PORK_CHOP_H__
#define __PORK_CHOP_H__

#define  PORK_CHOP_Y 0.0975F

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define PORK_CHOP_WIDTH 30
#define PORK_CHOP_HEIGHT 30
#define PORK_CHOP_SPRITE "Resources\\Sprites\\PorkChop\\PorkChop.png"

class PorkChop : public CObject, M2DXBaseSprite
{
public:
	PorkChop(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~PorkChop() {};
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
