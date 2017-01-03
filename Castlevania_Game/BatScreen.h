#pragma once

#include "m2dxbasesprite.h"
#include "m2dxanimatedsprite.h"

#define BAT_FRAME_1 "CastleFrame1"
#define BAT_FRAME_2 "CastleFrame2"
#define BAT_FRAME_3 "CastleFrame3"
#define BAT_FRAME_4 "CastleFrame4"
#define BAT_FRAME_5 "CastleFrame5"
#define BAT_FRAME_6 "CastleFrame6"
#define BAT_FRAME_7 "CastleFrame7"
#define BAT_FRAME_8 "CastleFrame8"
#define BAT_FRAME_9 "CastleFrame9"
#define BAT_FRAME_10 "CastleFrame10"
#define BAT_FRAME_11 "CastleFrame11"
#define BAT_FRAME_12 "CastleFrame12"
#define BAT_FRAME_13 "CastleFrame13"
#define BAT_FRAME_14 "CastleFrame14"
#define BAT_FRAME_15 "CastleFrame15"

#define BAT_SHEET "TileScreen\\BatScreenSheet"


class BatScreen: public M2DXAnimatedSprite
{
	enum State
	{
		Begin,
		End
	};
public:
	BatScreen(int X, int Y);
	void Update(int deltaTime);
	void Draw();
	BatScreen() {};
	~BatScreen() {};
protected:
	int getAnimateRate() override { return 15; };
	string getNextFrame() override;
private:
	State currentState;
	void updateState();
};

