#include "MoneyBag400.h"
#include "SimonBelmont.h"


MoneyBag400::MoneyBag400(int X, int Y) : CObject(33, X, Y, MONEY_BAG_400_WIDTH, MONEY_BAG_400_HEIGHT, 0)
{
	_vy = MONEY_BAG_Y;
	initWithTexture(MONEY_BAG_400_SHEET);
	setCurrentFrame(MONEY_BAG_400);
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void MoneyBag400::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool MoneyBag400::updateCollis(CObject * Ob)
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
				Score::getInstance()->score += 400;
			}
			break;
			}
		}
	}
	return false;
}

void MoneyBag400::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void MoneyBag400::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void MoneyBag400::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void MoneyBag400::Draw()
{
	M2DXAnimatedSprite::draw();
}