#include "Bomerang.h"
#include "Camera.h"

Bomerang::Bomerang(int X, int Y, bool AD) : CObject(19, X,  Y , BOMERANG_WIDTH, BOMERANG_HEIGHT, 0)
{
	initWithTexture(BOMERANG_SHEET);
	setCurrentFrame(BOMERANG_FRAME_1);
	velocity.y = 0;
	setPosition(M2DXPoint(X, Y));
	if (AD == true)
	{
		this->AD = Left;
		velocity.x = -VELOCITY;
	}
	else
	{
		this->AD = Right;
		velocity.x = VELOCITY;
	}
	
}

Bomerang::~Bomerang()
{

}

void Bomerang::Update(int deltaTime, CObject* simon)
{
	if (!isDead)
	{
		M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
		swept->delta = deltaTime;
		{
			updateFrame(deltaTime);

			updateVelocityX(deltaTime);

			updateDirection();

			updatePosition(deltaTime);

			updateBomerangState(simon);

			updateInfor();
		}
	}
}

string Bomerang::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	if (velocity.x >= -0.0090820 && velocity.x <= 0.0090820)
		return BOMERANG_FRAME_1;
	if (currentFrame == BOMERANG_FRAME_1)
		return BOMERANG_FRAME_2;
	if (currentFrame == BOMERANG_FRAME_2)
		return BOMERANG_FRAME_3;
	if (currentFrame == BOMERANG_FRAME_3)
		return BOMERANG_FRAME_1;
}

void Bomerang::updateDirection()
{
	if (canChange == true)
	{
		if (AD == Left && velocity.x > 0)
			canChange = false;
		if (AD == Right && velocity.x < 0)
			canChange = false;
		if (AD == Left && _x <= Camera::getInstance()->getBound().left)
		{
			velocity.x = -0.0090820;
			canChange = false;
		}
		if (AD == Right && _x + _width >= Camera::getInstance()->getBound().right)
		{
			velocity.x = 0.0090820;
			canChange = false;
		}
	}
}

void Bomerang::updateVelocityX(int deltaTime)
{
	if (AD == Left)
		velocity.x += GRAVITY*deltaTime;
	else
		velocity.x -= GRAVITY*deltaTime;
}

void Bomerang::updateBomerangState(CObject* simon)
{
	if (!isDead)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		swept->CheckCollision(_box,simon->_box);
		if (!swept->AABBCheck(_box, boxCam))
		{
			M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
			isDead = true;
		}
		if (swept->direc != SweptAABB::Direction::None && canChange == false)
		{
			M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
			isDead = true;
		}
	}
}

void Bomerang::updateInfor()
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_width = getSize().width * 2;
	_height = getSize().height * 2;
	_vx = velocity.x;
	_vy = velocity.y;
	_box.x = _x;
	_box.y = _y;
	_box.w = _width;
	_box.h = _height;
	_box.vx = _vx;
	_box.vy = _vy;
}


void Bomerang::updatePosition( int deltaTime)
{
	auto position = getPosition();
	position += velocity * deltaTime;
	setPosition(position);
}

void Bomerang::Draw()
{
	M2DXAnimatedSprite::draw();
}