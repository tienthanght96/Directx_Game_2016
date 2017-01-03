#include "HolyWater.h"
#include "Camera.h"

HolyWater::HolyWater(int X, int Y, bool AD) : CObject(20, X, Y, HOLY_WATER_WIDTH, HOLY_WATER_HEIGHT, 0)
{
	initWithTexture(HOLY_WATER_SHEET);
	setCurrentFrame(HOLY_WATER_FRAME_1);
	setState(CObject::State::alive);
	velocity.y = -HOLY_WATER_Y;
	setPosition(M2DXPoint(X, Y));
	if (AD == true)
		velocity.x = -HOLY_WATER_X;
	else
		velocity.x = HOLY_WATER_X;
	remainingDead = 1000;
	M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\splashwater"));
}

HolyWater::~HolyWater()
{

}

void HolyWater::Update(int deltaTime, CObject* simon)
{
	if (!isDead)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		if (swept->AABBCheck(_box, boxCam))
		{
			swept->delta = deltaTime;

			updateState(deltaTime);

			updateFrame(deltaTime);

			updatePosition(simon, deltaTime);

			updateInfor();
		}
		else
			isDead = true;
	}
}

string HolyWater::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (currentState)
	{
	case State::alive:
		return HOLY_WATER_FRAME_1;
		break;
	case State::before_dead:
		if (currentFrame == HOLY_WATER_FRAME_1 || currentFrame == HOLY_WATER_FRAME_4)
			return HOLY_WATER_FRAME_2;
		if (currentFrame == HOLY_WATER_FRAME_2)
			return HOLY_WATER_FRAME_3;
		if (currentFrame == HOLY_WATER_FRAME_3)
			return HOLY_WATER_FRAME_4;
		break;
	case State::dead:
		return "";
		break;
	}
}

void HolyWater::updateState(int deltaTime)
{
	switch (currentState)
	{
	case State::alive:
		break;
	case State::before_dead:
		velocity.x = 0;
		velocity.y = 0;
		remainingDead -= deltaTime;
		if (remainingDead <= 0)
			setState(State::dead);
		break;
	case State::dead:
		isDead = true;
		break;
	}
}

void HolyWater::updateInfor()
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_width = getSize().width * 2;
	_height = getSize().height * 2;
	if (currentState == State::alive)
	_vx = velocity.x;
	else
		if (currentState == State::before_dead)
			_vx = 1;
	_vy = velocity.y;
	_box.x = _x;
	_box.y = _y;
	_box.w = _width;
	_box.h = _height;
	_box.vx = _vx;
	_box.vy = _vy;
}


void HolyWater::updatePosition(CObject* simon, int deltaTime)
{
	if (currentState == State::alive)
	velocity.y += GRAVITY*deltaTime;
	auto position = getPosition();
	position += velocity * deltaTime;
	setPosition(position);
}

void HolyWater::Draw()
{
	M2DXAnimatedSprite::draw();
}