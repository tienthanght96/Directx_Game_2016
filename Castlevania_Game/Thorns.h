#ifndef __THORNS_H__
#define __THORNS_H__

#define  THORNS_Y 0.0975F

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define THORNS_WIDTH 64	
#define THORNS_HEIGHT 18
#define THORNS_SPRITE "Resources\\Sprites\\Thorns\\Thorns.png"
#define TIME_TO_DRAW 1

class Thorns : public CObject, M2DXBaseSprite
{
public:
	Thorns(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~Thorns() {};
private:
	float distance;
	int remainingDraw;
	int n;
	M2DXBaseSprite *chain;
	void updateChain();
	int positionY;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
