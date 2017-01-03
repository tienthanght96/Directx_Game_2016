#ifndef __WEPONS_ITEM_H__
#define __WEPONS_ITEM_H__

#define  WEPONS_ITEM_Y 0.0975F

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"
#define WEPONS_ITEM_WIDTH 30
#define WEPONS_ITEM_HEIGHT 30
#define AXE_ITEM_SPRITE "Resources\\Sprites\\WeaponsItem\\Axe"
#define BOOMERANG_ITEM_SPRITE "Resources\\Sprites\\WeaponsItem\\Boomerang"
#define DAGGER_ITEM_SPRITE "Resources\\Sprites\\WeaponsItem\\Dagger"
#define FIREBOMB_ITEM_SPRITE "Resources\\Sprites\\WeaponsItem\\FireBomb"
#define WATCH_ITEM_SPRITE "Resources\\Sprites\\WeaponsItem\\Watch"

class WeponsItem : public CObject, M2DXBaseSprite
{
public:
	WeponsItem(int ID, int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~WeponsItem() {};
private:
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
