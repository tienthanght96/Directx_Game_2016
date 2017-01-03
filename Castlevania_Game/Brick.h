#ifndef __BRICK_H__
#define __BRICK_H__

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32
#define BRICK_SPRITE "tile\\2-2.png"

class Brick : public CObject, M2DXBaseSprite
{
public:
	Brick(int X, int Y, int W, int H, int item);
	M2DXBaseSprite brick;
	SweptAABB *swept = new SweptAABB();
	virtual void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	virtual void Render();
	void Draw();
	Brick();
	~Brick();
};

#endif
