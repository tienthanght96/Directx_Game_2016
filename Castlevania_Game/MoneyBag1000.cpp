#include "Moneybag1000.h"
#include "SimonBelmont.h"
#include "Camera.h"


MoneyBag1000::MoneyBag1000(int X, int Y) : CObject(35, X, Y, MONEY_BAG_1000_WIDTH, MONEY_BAG_1000_HEIGHT, 0)
{
	positionY = Y;
	initWithTexture(MONEY_BAG_1000_SHEET);
	setCurrentFrame(MONEY_BAG_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2 + 16));
	visible = false;
}

void MoneyBag1000::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(_box, boxCam))
	{
		if (visible == true)
		{
			swept->delta = DeltaTime;
			updateFrame();
			updatePosition(DeltaTime);
			updateState(DeltaTime);
			updateInfor(DeltaTime);
		}
		else
			updateVisible(DeltaTime);
	}
}

bool MoneyBag1000::updateCollis(CObject * Ob)
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

string MoneyBag1000::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	if (currentFrame == MONEY_BAG_FRAME_1)
		return MONEY_BAG_FRAME_2;
	if (currentFrame == MONEY_BAG_FRAME_2)
		return MONEY_BAG_FRAME_3;
	if (currentFrame == MONEY_BAG_FRAME_3)
		return MONEY_BAG_FRAME_1;
}

void MoneyBag1000::updateFrame()
{
	setCurrentFrame(getNextFrame());
}

void MoneyBag1000::updateVisible(int deltaTime)
{
	if (remainingVisible > 0)
	{
		if (simonPointX - 160 >= _x)
			remainingVisible -= deltaTime;
		visible = false;
	}
	else
		visible = true;
}

void MoneyBag1000::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void MoneyBag1000::updatePosition(int deltaTime)
{
	if (_y / 2 > positionY)
		setPositionY(getPositionY() - 1);
}

void MoneyBag1000::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void MoneyBag1000::Draw()
{
	if (visible == true)
		M2DXAnimatedSprite::draw();
}