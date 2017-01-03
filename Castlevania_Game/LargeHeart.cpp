#include "LargeHeart.h"
#include "Heart.h"


LargeHeart::LargeHeart(int X, int Y) : CObject(31, X, Y, LARGE_HEART_WIDTH, LARGE_HEART_HEIGHT, 0)
{
	_vy = LARGE_HEART_Y;
	initWithTexture(LARGE_HEART_SHEET);
	setCurrentFrame(LARGE_HEART);
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void LargeHeart::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool LargeHeart::updateCollis(CObject * Ob)
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
				Heart::getInstance()->heart += 5;
			}
			break;
			}
		}
	}
	return false;
}

void LargeHeart::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void LargeHeart::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void LargeHeart::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void LargeHeart::Draw()
{
	M2DXAnimatedSprite::draw();
}