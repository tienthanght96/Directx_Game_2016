#ifndef __TREASURE_CHEST_H__
#define __TREASURE_CHEST_H__

#define  TREASURE_CHEST_FRAME_1 "TreasureChestFrame1"
#define  TREASURE_CHEST_FRAME_2 "TreasureChestFrame2"
#define  TREASURE_CHEST_FRAME_3 "TreasureChestFrame3"
#define  TREASURE_CHEST_FRAME_4 "TreasureChestFrame4"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"

#define TREASURE_CHEST_WIDTH 30
#define TREASURE_CHEST_HEIGHT 30
#define TREASURE_CHEST_SPRITE "Resources\\Sprites\\TreasureChest\\TreasureChestSheet.png"
#define TREASURE_CHEST_SHEET "Resources\\Sprites\\TreasureChest\\TreasureChestSheet"

class TreasureChest : public CObject, M2DXAnimatedSprite
{
public:
	TreasureChest(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~TreasureChest() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override;
private:
	int positionY;
	void updateFrame();
	void updateVisible(int deltaTime);
	int remainingVisible = 5000;
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
