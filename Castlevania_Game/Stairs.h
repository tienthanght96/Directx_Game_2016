#ifndef __STAIRSUP_H__
#define __STAIRSUP_H__

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define STAIR_WIDTH 32
#define STAIR_HEIGHT 32

class Stairs : public CObject, M2DXBaseSprite
{
public:
	Stairs(int type, int X, int Y, int item);
	SweptAABB *swept = new SweptAABB();
	virtual void Update(int DeltaTime);
	virtual bool updateCollis(CObject* Ob) { return false; };
	virtual void Render();
	void Draw();
	Stairs();
	~Stairs();
};

#endif
