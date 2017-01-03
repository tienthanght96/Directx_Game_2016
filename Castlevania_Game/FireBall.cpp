#include "FireBall.h"
#include "SimonBelmont.h"


FireBall::FireBall(int X, int Y, AttackDirection direc) : CObject(29, X, Y, FIRE_BALL_WIDTH, FIRE_BALL_HEIGHT, 0)
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
	initWithTexture(FIRE_BALL_SHEET);
	setCurrentFrame(FIRE_BALL);
	setPosition(M2DXPoint(_x / 2, _y / 2));

}

void FireBall::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updatePosition(DeltaTime);

	updateInfor(DeltaTime);
}

bool FireBall::updateCollis(CObject * Ob)
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
			}
		}
	}
	return false;
}

void FireBall::updatePosition(int deltaTime)
{
	auto positionX = getPositionX() + _vx * deltaTime;
	setPositionX(positionX);
}

void FireBall::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = 0;
}

void FireBall::Draw()
{
	M2DXAnimatedSprite::draw();
}