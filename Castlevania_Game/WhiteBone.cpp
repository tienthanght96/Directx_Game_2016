#include "WhiteBone.h"
#include "SimonBelmont.h"


WhiteBone::WhiteBone(int X, int Y, AttackDirection direc) : CObject(27, X, Y, WHITE_BONE_WIDTH, WHITE_BONE_HEIGHT, 0)
{
	if (direc == Left)
	{
		_vx = -WHITEBONE_X;
		setFlipX(true);
	}
	else
	{
		_vx = WHITEBONE_X;
		setFlipX(false);
	}
	_vy = WHITEBONE_Y;
	initWithTexture(WHITE_BONE_SHEET);
	setCurrentFrame(WHITE_BONE_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));

}

void WhiteBone::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateFrame(DeltaTime);

	updatePosition(DeltaTime);

	updateInfor(DeltaTime);
}

bool WhiteBone::updateCollis(CObject * Ob)
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

string WhiteBone::getNextFrame()
{
	auto currentFrane = getCurrentFrame();
	switch (getCurrentState())
	{
	case CObject::State::alive:
	{
		if (currentFrane == WHITE_BONE_FRAME_1)
			return WHITE_BONE_FRAME_2;
		if (currentFrane == WHITE_BONE_FRAME_2)
			return WHITE_BONE_FRAME_3;
		else
			return WHITE_BONE_FRAME_1;
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

void WhiteBone::updatePosition(int deltaTime)
{
	_vy += GRAVITY * deltaTime;
	auto positionX = getPositionX() + _vx * deltaTime;
	auto positionY = getPositionY() + _vy * deltaTime;
	setPosition(M2DXPoint(positionX, positionY));
}

void WhiteBone::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void WhiteBone::Draw()
{
	M2DXAnimatedSprite::draw();
}