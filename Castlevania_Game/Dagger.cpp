#include "Dagger.h"
#include "Camera.h"

Dagger::Dagger(int X, int Y, bool AD) : CObject(26, X, Y, DAGGER_WIDTH, DAGGER_HEIGHT, 0)
{
	initWithTexture(DAGGER_SHEET);
	setCurrentFrame(DAGGER);
	velocity.y = -0.01825F;
	setPosition(M2DXPoint(X, Y));
	if (AD == true)
	{
		velocity.x = -DAGGER_X;
		setFlipX(true);
	}
	else
	{
		velocity.x = DAGGER_X;
		setFlipX(false);
	}
	M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\splashwater"));
}

Dagger::~Dagger()
{

}

void Dagger::Update(int deltaTime, CObject* simon)
{
	if (!isDead)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		if (swept->AABBCheck(_box, boxCam))
		{
			swept->delta = deltaTime;
			updateFrame(deltaTime);

			updatePosition(simon, deltaTime);

			updateInfor();
		}
		else
			isDead = true;
	}
}

void Dagger::updateInfor()
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


void Dagger::updatePosition(CObject* simon, int deltaTime)
{
	auto position = getPosition();
	position += velocity * deltaTime;
	setPosition(position);
}

void Dagger::Draw()
{
	M2DXAnimatedSprite::draw();
}