#include "SmallHeart.h"


SmallHeart::SmallHeart(int X, int Y) : CObject(30, X, Y, SMALL_HEART_WIDTH, SMALL_HEART_HEIGHT, 0)
{
	gravity = GRAVITY;
	_vy = SMALL_HEART_Y;
	_vx = SMALL_HEART_X;
	initWithTexture(SMALL_HEART_SHEET);
	setCurrentFrame(SMALL_HEART);
	setPosition(M2DXPoint(_x/2 ,_y/2));
}

void SmallHeart::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool SmallHeart::updateCollis(CObject * Ob)
{
	if (!isDead)
	{
		swept->CheckCollision(_box, Ob->_box);
			if(swept->direc != SweptAABB::Direction::None)
		{
				switch(Ob->_type)
				{
				case 2:
				{
					if (swept->direc == SweptAABB::Direction::Bottom)
					{
						setPositionY(Ob->_box.y / 2 - _box.h / 2);
						_vy = 0;
						_vx = 0;
						isFall = false;
					}
				}
				break;
				case 1:
				{
					isDead = true;
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\collectitem"));
					Heart::getInstance()->heart += 1;
				}
				break;
				}
		}
	}
	return false;
}

void SmallHeart::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void SmallHeart::updatePosition(int deltaTime)
{
	if (_vx >= SMALL_HEART_X)
		gravity = -GRAVITY;
	else
		if (_vx <= -SMALL_HEART_X)
			gravity = GRAVITY;
	if (isFall == true)
	_vx += gravity*deltaTime;
	auto positionX = getPositionX() + _vx * deltaTime;
	auto positionY = getPositionY() + _vy * deltaTime;
	setPosition(M2DXPoint(positionX,positionY));
}

void SmallHeart::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void SmallHeart::Draw()
{
	M2DXAnimatedSprite::draw();
}