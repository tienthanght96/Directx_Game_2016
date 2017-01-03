#include "MorningStar.h"
#include "SimonBelmont.h"


MorningStar::MorningStar(int X, int Y) : CObject(38, X, Y, MORNING_STAR_WIDTH, MORNING_STAR_HEIGHT, 0)
{
	_vy = MORNING_STAR_Y;
	initWithTexture("Resources\\Sprites\\WeaponsItem\\MorningStar");
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void MorningStar::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool MorningStar::updateCollis(CObject * Ob)
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
				Stage::getInstance()->levelWhip += 1;
				if (Stage::getInstance()->levelWhip > 2)
					Stage::getInstance()->levelWhip = 2;
				SimonBelmont* temp = (SimonBelmont*)Ob;
				temp->remainingGetMorningStar = 1000;
			}
			break;
			}
		}
	}
	return false;
}

void MorningStar::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void MorningStar::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void MorningStar::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void MorningStar::Draw()
{
	M2DXBaseSprite::draw();
}