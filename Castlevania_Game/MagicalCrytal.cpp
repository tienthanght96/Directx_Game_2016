#include "MagicalCrytal.h"
#include "Heart.h"
#include "BloodManager.h"
#include "SimonBelmont.h"


MagicalCrytal::MagicalCrytal(int X, int Y) : CObject(25, X, Y, MAGICAL_CRYTAL_WIDTH, MAGICAL_CRYTAL_HEIGHT, 0)
{
	_vy = VELOCITY_Y;
	initWithTexture(MAGICAL_CRYTAL_SHEET);
	setCurrentFrame(MAGICAL_CRYTAL_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	color = 100;
}

void MagicalCrytal::Update(int DeltaTime)
{
	if (color < 255)
	{
		color = color + 5;
	}
	else
	{
		swept->delta = DeltaTime;
		updateFrame(DeltaTime);
		updatePosition(DeltaTime);
		updateInfor(DeltaTime);
	}
}

bool MagicalCrytal::updateCollis(CObject * Ob)
{
	if (color >= 255)
	{
		if (!isDead)
		{
			swept->CheckCollision(_box, Ob->_box);
			if (swept->direc != SweptAABB::Direction::None)
			{
				switch (Ob->_type)
				{
				case 2:
				{
					if (swept->direc == SweptAABB::Direction::Bottom)
					{
						setPositionY(Ob->_box.y / 2 - _box.h / 2);
						_vy = 0;
					}
				}
				break;
				case 1:
				{
					isDead = true;
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\collectitem"));
					Score::getInstance()->score += 1000;
					BloodManager::getInstance()->bloodSimon = 16;
					M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Boss"));
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Stage_Clear"));
				}
				break;
				}
			}
		}
	}
	return false;
}

string MagicalCrytal::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	if (currentFrame == MAGICAL_CRYTAL_FRAME_1)
		return MAGICAL_CRYTAL_FRAME_2;
	else
		return MAGICAL_CRYTAL_FRAME_1;
}

void MagicalCrytal::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void MagicalCrytal::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void MagicalCrytal::Draw()
{
	if (color > 255)
		color = 255;
	M2DXAnimatedSprite::draw(D3DCOLOR_ARGB(color,255,255,255));
}