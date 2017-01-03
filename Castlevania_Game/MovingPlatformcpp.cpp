#include "MovingPlatform.h"
#include "Camera.h"



MovingPlatform::MovingPlatform(int X, int Y, int item) : CObject(18, X, Y, PLATFORM_WIDTH, PLATFORM_HEIGHT, 0)
{
	_vx = MOVING_PLATFORM_SPEED;
	initWithTexture(PLATFORM_SHEET);
	setCurrentFrame(MOVING_PLATFORM);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	isMovement = true;
}

void MovingPlatform::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(_box, boxCam))
	{
		updatePosition(DeltaTime);
		updateInfor(DeltaTime);
	}
}

bool MovingPlatform::updateCollis(CObject * Ob)
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
				if (swept->direc == SweptAABB::Direction::Left)
				{
					_vx = MOVING_PLATFORM_SPEED;
				}
				if (swept->direc == SweptAABB::Direction::Right)
					_vx = -MOVING_PLATFORM_SPEED;
			}
			break;
			}
		}
	}
	return false;
}

void MovingPlatform::updatePosition(int deltaTime)
{
	auto positionX = getPositionX() + _vx * deltaTime;
	setPositionX(positionX);
}

void MovingPlatform::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = 0;
}

void MovingPlatform::Draw()
{
	M2DXAnimatedSprite::draw();
}