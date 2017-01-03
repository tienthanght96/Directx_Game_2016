#ifndef __FLAME_HIT_H__
#define __FLAME_HIT_H__

#define FLAME_HIT_DEFAULT_ANIMATE_RATE 6

#define FLAME_HIT_FRAME_1 "FlameHitFrame1"
#define FLAME_HIT_FRAME_2 "FlameHitFrame2"
#define FLAME_HIT_FRAME_3 "FlameHitFrame3"
#define FLAME_HIT_FRAME_4 "FlameHitFrame4"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"


#define FLAME_HIT_WIDTH 16
#define FLAME_HIT_HEIGHT 30
#define FLAME_HIT_SPRITE "Resources\\Sprites\\FlameHit\\FlameHitSheet.png"
#define FLAME_HIT_SHEET "Resources\\Sprites\\FlameHit\\FlameHitSheet"


class FlameHit : public CObject, M2DXAnimatedSprite
{
public:
	FlameHit(int X, int Y, int item);
	void Update(int DeltaTime);
	void Draw();
	FlameHit() {};
	~FlameHit() {};
protected:
	int getAnimateRate() override;
	string getNextFrame() override;
};

#endif
