#include "Axe.h"
#include "Camera.h"

Axe::Axe(int X, int Y, bool AD) : CObject(19, X, Y, AXE_WIDTH, AXE_HEIGHT, 0)
{
	initWithTexture(AXE_SHEET);
	setCurrentFrame(AXE_FRAME_1);
	velocity.y = - VELOCITY_Y;
	setPosition(M2DXPoint(X, Y));
	if (AD == true)
		velocity.x = -VELOCITY_X;
	else
		velocity.x = VELOCITY_X;	
	M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\splashwater"));
}

Axe::~Axe()
{

}

void Axe::Update(int deltaTime, CObject* simon)
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

string Axe::getNextFrame()
{
	auto currentFrame = getCurrentFrame();	
	if (currentFrame == AXE_FRAME_1)
		return AXE_FRAME_2;
	if (currentFrame == AXE_FRAME_2)
		return AXE_FRAME_3;
	if (currentFrame == AXE_FRAME_3)
		return AXE_FRAME_4;
	if (currentFrame == AXE_FRAME_4)
		return AXE_FRAME_1;
}

void Axe::updateInfor()
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


void Axe::updatePosition(CObject* simon,int deltaTime)
{
	velocity.y += GRAVITY*deltaTime;

	auto position = getPosition();
	position += velocity * deltaTime;
	setPosition(position);
}

void Axe::Draw()
{
	M2DXAnimatedSprite::draw();
}