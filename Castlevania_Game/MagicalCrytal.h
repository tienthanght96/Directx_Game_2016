#ifndef __MAGICAL_CRYTAL_H__
#define __MAGICAL_CRYTAL_H__

#define MAGICAL_CRYTAL_Y 0.1875F

#define MONEY_BAG_DEFAULT_RATE 15

#define  MAGICAL_CRYTAL_FRAME_1 "MagicalCrystalFrame1"
#define  MAGICAL_CRYTAL_FRAME_2 "MagicalCrystalFrame2"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "Global.h"

#define MAGICAL_CRYTAL_WIDTH 28
#define MAGICAL_CRYTAL_HEIGHT 32
#define MAGICAL_CRYTAL_SPRITE "Resources\\Sprites\\MagicalCrystal\\MagicalCrystalSheet.png"
#define MAGICAL_CRYTAL_SHEET "Resources\\Sprites\\MagicalCrystal\\MagicalCrystalSheet"

class MagicalCrytal : public CObject, M2DXAnimatedSprite
{
public:
	MagicalCrytal(int X, int Y);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void Draw();
	~MagicalCrytal() {};
protected:
	int getAnimateRate() override { return MONEY_BAG_DEFAULT_RATE; };
	string getNextFrame() override;
private:
	int color = 100;
	void updatePosition(int deltaTime);
	void updateInfor(int deltaTime);
};

#endif
