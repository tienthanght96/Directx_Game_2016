#ifndef __CROSS_H__
#define __CROSS_H__

#define  CROSS_Y 0.0975F

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define CROSS_WIDTH 30
#define CROSS_HEIGHT 30
#define CROSS_SPRITE "Resources\\Sprites\\Cross.png"

class Cross : public CObject, M2DXBaseSprite
{
public:
	Cross(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~Cross() {};
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
