#include "Crown.h"
#include "SimonBelmont.h"


Crown::Crown(int X, int Y) : CObject(45, X, Y, CROWN_WIDTH, CROWN_HEIGHT, 0)
{
	positionY = Y;
	initWithTexture(CROWN_SHEET);
	setCurrentFrame(CROWN_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2 + 16));
}

void Crown::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updateFrame();
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool Crown::updateCollis(CObject * Ob)
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
				M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\collectitem"));
				Score::getInstance()->score += 2000;
			}
			break;
			}
		}
	}
	return false;
}

string Crown ::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	if (currentFrame == CROWN_FRAME_1)
		return CROWN_FRAME_2;
	if (currentFrame == CROWN_FRAME_2)
		return CROWN_FRAME_3;
	if (currentFrame == CROWN_FRAME_3)
		return CROWN_FRAME_4;
	if (currentFrame == CROWN_FRAME_4)
		return CROWN_FRAME_1;
}

void Crown::updateFrame()
{
	setCurrentFrame(getNextFrame());
}

void Crown::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void Crown::updatePosition(int deltaTime)
{
	if (_y / 2 > positionY)
		setPositionY(getPositionY() - 1);
}

void Crown::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void Crown::Draw()
{
	M2DXAnimatedSprite::draw();
}