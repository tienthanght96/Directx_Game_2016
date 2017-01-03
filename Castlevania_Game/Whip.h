#pragma once

#include "SimonBelmont.h"
#include "CObject.h"
#include "Box.h"
#define WHIP_SPRITE_SHEET_PATH "Resources\\Sprites\\Weapons\\Whip\\WhipSpriteSheet.png"
#define WHIP_TEXTURE_NAME "Resources\\Sprites\\Weapons\\Whip\\WhipSpriteSheet"

#define VAMPIRE_KILLER_ANIMATE_RATE 1
#define CHAIN_WHIP_ANIMATE_RATE 1
#define MORNING_STAR_ANIMATE_RATE 8

#define VAMPIRE_KILLER_BEGIN_FRAME_NAME "VampireKillerBegin"
#define VAMPIRE_KILLER_MIDDLE_FRAME_NAME "VampireKillerMiddle"
#define VAMPIRE_KILLER_END_FRAME_NAME "VampireKillerEnd"
#define CHAIN_WHIP_BEGIN_FRAME_NAME "ChainWhipBegin"
#define CHAIN_WHIP_MIDDLE_FRAME_NAME "ChainWhipMiddle"
#define CHAIN_WHIP_END_FRAME_NAME "ChainWhipEnd"
#define MORNING_STAR_BEGIN_FRAME_NAME_0 "MorningStarBegin0"
#define MORNING_STAR_BEGIN_FRAME_NAME_1 "MorningStarBegin1"
#define MORNING_STAR_BEGIN_FRAME_NAME_2 "MorningStarBegin2"
#define MORNING_STAR_MIDDLE_FRAME_NAME_0 "MorningStarMiddle0"
#define MORNING_STAR_MIDDLE_FRAME_NAME_1 "MorningStarMiddle1"
#define MORNING_STAR_MIDDLE_FRAME_NAME_2 "MorningStarMiddle2"
#define MORNING_STAR_END_FRAME_NAME_0 "MorningStarEnd0"
#define MORNING_STAR_END_FRAME_NAME_1 "MorningStarEnd1"
#define MORNING_STAR_END_FRAME_NAME_2 "MorningStarEnd2"

class Whip : public M2DXAnimatedSprite, CObject
{
public:
	enum WhipType
	{
		VampireKiller,
		ChainWhip,
		MorningStar
	};

	enum WhipUsingState
	{
		None,
		Begin,
		Middle,
		End
	};

	Whip();
	Whip(int level);
	~Whip();

	Box getBox()
	{
		Box temp(getPositionX() * 2, getPositionY()* 2, getSize().width * 2, getSize().height * 2);
		return temp;
	}
	bool canDamage = false;
	void Update(int deltaTime,CObject* simon);
	/*bool canDamaged;*/
	void Draw() override;
	WhipUsingState usingState;
protected:
	string getNextFrame() override;
	int getAnimateRate() override { return 0; } // Not used.
	void updateFrame();

private:
	WhipType type;
	void updateInfor();
	void updateState(CObject* player);
	void updatePosition(CObject* player);
};