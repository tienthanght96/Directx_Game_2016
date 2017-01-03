#include "MoneyBag100.h"
#include "SimonBelmont.h"


MoneyBag100::MoneyBag100(int X, int Y) : CObject(32, X, Y, MONEY_BAG_100_WIDTH, MONEY_BAG_100_HEIGHT, 0)
{
	_vy = MONEY_BAG_Y;
	initWithTexture(MONEY_BAG_100_SHEET);
	setCurrentFrame(MONEY_BAG_100);
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void MoneyBag100::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool MoneyBag100::updateCollis(CObject * Ob)
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
				Score::getInstance()->score += 100;
			}
			break;
			}
		}
	}
	return false;
}

void MoneyBag100::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void MoneyBag100::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void MoneyBag100::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void MoneyBag100::Draw()
{
	M2DXAnimatedSprite::draw();
}