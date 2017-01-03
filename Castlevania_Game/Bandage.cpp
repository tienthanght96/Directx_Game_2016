#include "Bandage.h"
#include "SimonBelmont.h"


Bandage::Bandage(int X, int Y, AttackDirection direc) : CObject(26, X, Y, BANDAGE_WIDTH, BANDAGE_HEIGHT, 0)
{
	if (direc == Left)
	{
		_vx = -BANDAGE_X;
		setFlipX(true);
	}
	else
	{
		_vx = BANDAGE_X;
		setFlipX(false);
	}
	defaultY = _y;
	gravity = GRAVITY;
	_vy = -BANDAGE_Y;
	initWithTexture(BANDAGE_SHEET);
	setCurrentFrame(BANDAGE_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));

}

void Bandage::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateFrame(DeltaTime);

	updatePosition(DeltaTime);

	updateInfor(DeltaTime);
}

bool Bandage::updateCollis(CObject * Ob)
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

string Bandage::getNextFrame()
{
	auto currentFrane = getCurrentFrame();
	switch (getCurrentState())
	{
	case CObject::State::alive:
	{
		if (currentFrane == BANDAGE_FRAME_1)
			return BANDAGE_FRAME_2;
		else
			return BANDAGE_FRAME_1;
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

void Bandage::updatePosition(int deltaTime)
{
	if (_vy >= BANDAGE_Y)
		gravity = -GRAVITY;
	else
		if (_vy <= -BANDAGE_Y)
			gravity = GRAVITY;
	_vy = _vy + gravity * deltaTime;
	auto positionX = getPositionX();
	auto positionY = getPositionY();
	positionX += _vx * deltaTime;
	positionY += _vy * deltaTime;
	setPositionX(positionX);
	setPositionY(positionY);
}

void Bandage::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Bandage::Draw()
{
	M2DXAnimatedSprite::draw();
}