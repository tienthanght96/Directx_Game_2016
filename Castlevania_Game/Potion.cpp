#include "Potion.h"
#include "SimonBelmont.h"


Potion::Potion(int X, int Y) : CObject(49, X, Y, POTION_WIDTH, POTION_HEIGHT, 0)
{
	_vy = POTION_Y;
	initWithTexture("Resources\\Sprites\\ipotion");
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void Potion::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool Potion::updateCollis(CObject * Ob)
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
				SimonBelmont* temp = (SimonBelmont*)Ob;
				temp->remainingGetPotion = 4000;
			}
			break;
			}
		}
	}
	return false;
}

void Potion::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void Potion::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void Potion::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void Potion::Draw()
{
	M2DXBaseSprite::draw();
}