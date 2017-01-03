#include "TreasureChest.h"
#include "SimonBelmont.h"
#include "Camera.h"


TreasureChest::TreasureChest(int X, int Y) : CObject(46, X, Y, TREASURE_CHEST_WIDTH, TREASURE_CHEST_HEIGHT, 0)
{
	positionY = Y;
	initWithTexture(TREASURE_CHEST_SHEET);
	setCurrentFrame(TREASURE_CHEST_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2 + 16));
	visible = false;
}

void TreasureChest::Update(int DeltaTime)
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

bool TreasureChest::updateCollis(CObject * Ob)
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

string TreasureChest::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	if (currentFrame == TREASURE_CHEST_FRAME_1)
		return TREASURE_CHEST_FRAME_2;
	if (currentFrame == TREASURE_CHEST_FRAME_2)
		return TREASURE_CHEST_FRAME_3;
	if (currentFrame == TREASURE_CHEST_FRAME_3)
		return TREASURE_CHEST_FRAME_4;
	if (currentFrame == TREASURE_CHEST_FRAME_4)
		return TREASURE_CHEST_FRAME_1;
}

void TreasureChest::updateFrame()
{
	setCurrentFrame(getNextFrame());
}

void TreasureChest::updateVisible(int deltaTime)
{
	if (remainingVisible > 0)
	{
		if (simonPointX + 160 <= _x)
			remainingVisible -= deltaTime;
		visible = false;
	}
	else
		visible = true;
}

void TreasureChest::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void TreasureChest::updatePosition(int deltaTime)
{
	if (_y / 2 > positionY)
		setPositionY(getPositionY() - 1);
}

void TreasureChest::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void TreasureChest::Draw()
{
	if (visible == true)
	M2DXAnimatedSprite::draw();
}