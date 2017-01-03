#include "PorkChop.h"
#include "SimonBelmont.h"
#include "BloodManager.h"


PorkChop::PorkChop(int X, int Y) : CObject(39, X, Y, PORK_CHOP_WIDTH, PORK_CHOP_HEIGHT, 0)
{
	_vy = PORK_CHOP_Y;
	initWithTexture("Resources\\Sprites\\PorkChop\\PorkChop");
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void PorkChop::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool PorkChop::updateCollis(CObject * Ob)
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
				BloodManager::getInstance()->bloodSimon += 5;
				if (BloodManager::getInstance()->bloodSimon > 16)
					BloodManager::getInstance()->bloodSimon = 16;
			}
			break;
			}
		}
	}
	return false;
}

void PorkChop::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void PorkChop::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void PorkChop::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void PorkChop::Draw()
{
	M2DXBaseSprite::draw();
}