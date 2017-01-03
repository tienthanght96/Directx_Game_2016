#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "SweptAABB.h"
#include "CObject.h"
#include "WeponManager.h"
#include "m2dxbasesprite.h"
#include "ListChunk.h"

#define BLOCK_WIDTH 32
#define BLOCK_HEIGHT 32
#define BLOCK_SPRITE "Resources\\Sprites\\Broken.png"


class Block : public CObject, M2DXBaseSprite
{
public:
	Block(int X, int Y, int item);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	Block() {};
	~Block() {};
	void Restore()
	{
		setPosition(M2DXPoint(pointX, pointY));
		health = 50;
		initWithTexture("");
	}
private:
	bool allocated;
	int health = 50;
	ListChunk* _listChunk;
	vector<CObject*> listWepon;
	bool isExist(CObject* Ob);
	bool isExist(CObject* Ob, list<CObject*> listOb);
	void updateListWepon();
	void updateState(int deltaTime);
};

#endif
