#include "Snake.h"
#include "SimonBelmont.h"


Snake::Snake(int X, int Y, AttackDirection direc) : CObject(28, X, Y, SNAKE_WIDTH, SNAKE_HEIGHT, 0)
{
	if (direc == Left)
	{
		_vx = -VELOCITY_X;
		setFlipX(true);
	}
	else
	{
		_vx = VELOCITY_X;
		setFlipX(false);
	}
	_vy = VELOCITY_X;
	initWithTexture(SNAKE_SHEET);
	setCurrentFrame(SNAKE_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));

}

void Snake::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateFrame(DeltaTime);

	updatePosition(DeltaTime);

	updateInfor(DeltaTime);
}

bool Snake::updateCollis(CObject * Ob)
{
	if (!isDead)
	{
		swept->CheckCollision(_box, Ob->_box);
		if (swept->direc != SweptAABB::Direction::None)
		{
			switch (Ob->_type)
			{
			case 1:
			{
				isDead = true;
				SimonBelmont* temp = (SimonBelmont*)Ob;
				if (temp->getActionState() != SimonBelmont::ActionState::GettingDamaged)
				{
					temp->setactionState(SimonBelmont::ActionState::GettingDamaged);
					temp->gettingdamaged();
				}
			}
			break;
			case 2:
			{
				if (swept->direc == SweptAABB::Direction::Bottom)
				{
					setPositionY(Ob->_box.y / 2 - _box.h / 2);
					_vy = 0;
				}
			}
			break;
			}
		}
	}
	return false;
}

string Snake::getNextFrame()
{
	auto currentFrane = getCurrentFrame();
	switch (getCurrentState())
	{
	case CObject::State::alive:
	{
		if (currentFrane == SNAKE_FRAME_1)
			return SNAKE_FRAME_2;
		else
			return SNAKE_FRAME_1;
	}
	break;
	case CObject::State::before_dead:
		return "";
		break;
	case CObject::State::dead:
		return "";
		break;
	}
}

void Snake::updatePosition(int deltaTime)
{
	auto positionX = getPositionX() + _vx * deltaTime;
	auto positionY = getPositionY() + _vy * deltaTime;
	setPosition(M2DXPoint(positionX,positionY));
}

void Snake::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Snake::Draw()
{
	M2DXAnimatedSprite::draw();
}