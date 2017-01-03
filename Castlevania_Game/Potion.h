#ifndef __POTION_H__
#define __POTION_H__

#define  POTION_Y 0.0975F

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define POTION_WIDTH 30
#define POTION_HEIGHT 30
#define POTION_SPRITE "Resources\\Sprites\\ipotion.png"

class Potion : public CObject, M2DXBaseSprite
{
public:
	Potion(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~Potion() {};
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
