#ifndef __CROWN_H__
#define __CROWN_H__

#define  CROWN_FRAME_1 "CrownFrame1"
#define  CROWN_FRAME_2 "CrownFrame2"
#define  CROWN_FRAME_3 "CrownFrame3"
#define  CROWN_FRAME_4 "CrownFrame4"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"

#define CROWN_WIDTH 30
#define CROWN_HEIGHT 30
#define CROWN_SPRITE "Resources\\Sprites\\Crown\\CrownSheet.png"
#define CROWN_SHEET "Resources\\Sprites\\Crown\\CrownSheet"

class Crown : public CObject, M2DXAnimatedSprite
{
public:
	Crown(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~Crown() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override;
private:
	int positionY;
	void updateFrame();
	int remainingDead = 4000;
	void updateState(int deltaTime);
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
