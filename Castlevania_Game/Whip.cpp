#include "Whip.h"

Whip::Whip() : CObject(3, 0, 0, 0, 0, 0)
{
	initWithTexture(WHIP_TEXTURE_NAME);
	usingState = Whip::Begin;
	type = MorningStar;
	_vx = 1;
}

Whip::Whip(int level):CObject(3, 0, 0, 0, 0, 0)
{
	initWithTexture(WHIP_TEXTURE_NAME);
	usingState = Whip::Begin;
	switch(level)
	{
	case 1:
		type = WhipType::ChainWhip;
		break;
	case 0:
		type = WhipType::VampireKiller;
		break;
	case 2:
		type = WhipType::MorningStar;
		break;
	}
	_vx = 1;
}

Whip::~Whip()
{

}

void Whip::Update(int deltaTime,CObject* simon)
{

	updateState(simon);

	updateFrame();

	updatePosition(simon);

	updateInfor();
}

string Whip::getNextFrame()
{
	auto currentFrame = getCurrentFrame();

	switch (type)
	{
	case Whip::VampireKiller:
		switch (usingState)
		{
		case Whip::Begin:
			return VAMPIRE_KILLER_BEGIN_FRAME_NAME;
		case Whip::Middle:
			return VAMPIRE_KILLER_MIDDLE_FRAME_NAME;
		case Whip::End:
			return VAMPIRE_KILLER_END_FRAME_NAME;
		case Whip::None:
			return "";
			break;
		default:
			break;
		}
		break;
	case Whip::ChainWhip:
		switch (usingState)
		{
		case Whip::Begin:
			return CHAIN_WHIP_BEGIN_FRAME_NAME;
		case Whip::Middle:
			return CHAIN_WHIP_MIDDLE_FRAME_NAME;
		case Whip::End:
			return CHAIN_WHIP_END_FRAME_NAME;
		case Whip::None:
			return "";
			break;
		default:
			break;
		}
		break;
	case Whip::MorningStar:
		switch (usingState)
		{
		case Whip::Begin:
			if (currentFrame == MORNING_STAR_BEGIN_FRAME_NAME_0)
			{
				return MORNING_STAR_BEGIN_FRAME_NAME_1;
			}
			else if (currentFrame == MORNING_STAR_BEGIN_FRAME_NAME_1)
			{
				return MORNING_STAR_BEGIN_FRAME_NAME_2;
			}
			else
			{
				return MORNING_STAR_BEGIN_FRAME_NAME_0;
			}
			break;
		case Whip::Middle:
			if (currentFrame == MORNING_STAR_MIDDLE_FRAME_NAME_0)
			{
				return MORNING_STAR_MIDDLE_FRAME_NAME_1;
			}
			else if (currentFrame == MORNING_STAR_MIDDLE_FRAME_NAME_1)
			{
				return MORNING_STAR_MIDDLE_FRAME_NAME_2;
			}
			else
			{
				return MORNING_STAR_MIDDLE_FRAME_NAME_0;
			}
			break;
		case Whip::End:
			if (currentFrame == MORNING_STAR_END_FRAME_NAME_0)
			{
				return MORNING_STAR_END_FRAME_NAME_1;
			}
			else if (currentFrame == MORNING_STAR_END_FRAME_NAME_1)
			{
				return MORNING_STAR_END_FRAME_NAME_2;
			}
			else
			{
				return MORNING_STAR_END_FRAME_NAME_0;
			}
			break;
		case Whip::None:
			return "";
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Whip::updateFrame()
{
	setCurrentFrame(getNextFrame());
}

void Whip::updateInfor()
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_width = getSize().width * 2;
	_height = getSize().height * 2;
	_vx = 1;
	_vy = 0;
	_box.x = _x;
	_box.y = _y;
	_box.w = _width;
	_box.h = _height;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Whip::updateState(CObject* Ob)
{
	SimonBelmont* player = (SimonBelmont*)Ob;
	auto playerAttackState = player->getAttackState();

	switch (playerAttackState)
	{
	case SimonBelmont::Begin:
		usingState = Begin;
		
		break;
	case SimonBelmont::Middle:
		usingState = Middle;
		break;
	case SimonBelmont::End:
		usingState = End;
		M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\usingwhip"));
		break;
	case SimonBelmont::None:
		usingState = None;
		break;
	default:
		break;
	}
}

void Whip::updatePosition(CObject* Ob)
{
	SimonBelmont* player = (SimonBelmont*)Ob;
	auto whipPosition = player->getHandPosition();
	auto whipSize = getSize();
	auto flipX = player->getFlipX();

	switch (usingState)
	{
	case Whip::Begin:
		if (flipX)
		{
			whipPosition.x -= 1;
		}
		else
		{
			whipPosition.x -= whipSize.width - 1;
		}
		break;
	case Whip::Middle:
		if (flipX)
		{
			whipPosition.x -= 1;
		}
		else
		{
			whipPosition.x -= whipSize.width - 1;
		}
		break;
	case Whip::End:
		if (flipX)
		{
			whipPosition.x -= whipSize.width;
		}
		whipPosition.y -= whipSize.height - 3;
		break;
	default:
		break;
	}

	if (type == VampireKiller && usingState == End)
	{
		whipPosition.y -= 1;
	}
	

	setPosition(whipPosition);
	setFlipX(player->getFlipX());
}

void Whip::Draw()
{
	M2DXAnimatedSprite::draw();
}