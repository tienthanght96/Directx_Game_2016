#include "Door.h"

Door::Door(int X, int Y, int item) : CObject(10, X, Y, DOOR_WIDTH, DOOR_HEIGHT, item)
{
	defaultX = _x;
	defaultY = _y;
	initWithTexture(DOOR_SHEET);
	setPosition(M2DXPoint(_x/2, _y/2));
	setState(Begin);
	isMovement = false;
}

void Door::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition();

	updateFrame(DeltaTime);

	updateInfo();
}

bool Door::updateCollis(CObject * Ob)
{
	swept->CheckCollision(Ob->_box, _box);
	if (swept->direc != SweptAABB::Direction::None && Ob->_type == 1)
	{
		SimonBelmont* temp = (SimonBelmont*)Ob;
		switch (getState())
		{
		case DoorState::Begin:
			if (!temp->getFlipX())
			{
				temp->setPositionX(_x/2 - temp->getSize().width);
				setFlipX(false);
			}
			else
			{
				temp->setPositionX(_x/2 + _width/2);
				setFlipX(true);
			}
			setState(DoorState::Open);
			temp->setactionState(SimonBelmont::ActionState::Standing);
			Camera::getInstance()->changeState = true;
			break;
		case DoorState::Open:
			break;
		case DoorState::Midle:
			break;
		case DoorState::Close:
			break;
		case DoorState::End:
			if (temp->getFlipX() && temp->getPositionX() * 2 > _x)
			{
				if (temp->getPositionX() * 2 <= _x + _width)
					temp->setPositionX(_x / 2 + _width / 2);
			}
			else
				if (!temp->getFlipX() && temp->getPositionX() * 2 < _x)
				{
					if (temp->getPositionX() * 2 + temp->getSize().width * 2 >= _x)
						temp->setPositionX(_x / 2 - temp->getSize().width);
				}
			break;
		default:
			break;
		}
	}
	return false;
}

void Door::Draw()
{
	M2DXAnimatedSprite::draw();
}

int Door::getAnimateRate()
{
	switch (getState())
	{
	case Begin:
		return DOOR_BEGIN_RATE;
		break;
	case Open:
		return DOOR_DEFAULT_ANIMATE_RATE;
		break;
	case Midle:
		return DOOR_DEFAULT_ANIMATE_RATE;
		break;
	case Close:
		return DOOR_CLOSE_RATE;
		break;
	case End:
		return DOOR_DEFAULT_ANIMATE_RATE;
		break;
	}
	return 0;
}

string Door::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getState())
	{
	case DoorState::Begin:
		return DOOR_NORMAL;
		break;
	case DoorState::Open:
		if (currentFrame == DOOR_NORMAL)
		{
			M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\opendoor"));
			return DOOR_FRAME_BEGIN;
		}
		else
			return DOOR_FRAME_MIDLE;
		break;
	case DoorState::Midle:
		return DOOR_FRAME_MIDLE;
	case DoorState::Close:
		if (currentFrame == DOOR_FRAME_END_0)
			return DOOR_FRAME_END_1;
		else
			if (currentFrame == DOOR_FRAME_MIDLE)
			{
				M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\opendoor"));
				return DOOR_FRAME_END_0;
			}
			else 
				return DOOR_NORMAL;
		break;
	case DoorState::End:
		return DOOR_NORMAL;
		break;
	default:
		break;
	}
}

void Door::updateCamera(SimonBelmont* simon)
{
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left , viewPort.top , (viewPort.right - viewPort.left) , (viewPort.bottom - viewPort.top) );
	if(swept->AABBCheck(boxCam,_box))
	{
		switch (getState())
		{
		case Begin:
			if (simon->getPositionX() * 2 < _x)
			{
				if (simon->getPositionX() * 2 > (_x + _width) - Camera::getInstance()->width / 2)
				{
					Camera::getInstance()->setCamX(_x + _width - Camera::getInstance()->width / 2);
					Camera::getInstance()->setCam = true;
				}
			}
			else
				if (simon->getPositionX() * 2 > _x)
				{
					if (simon->getPositionX() * 2 < _x + Camera::getInstance()->width / 2)
					{
						Camera::getInstance()->setCamX(_x + Camera::getInstance()->width / 2);
						Camera::getInstance()->setCam = true;
					}
				}
			break;
		case Open:
			if (!simon->getFlipX())
			{
				if (simon->getPositionX() * 2 > Camera::getInstance()->cameraX)
					Camera::getInstance()->setCamX(Camera::getInstance()->cameraX + 3);
				else
					setState(Midle);
			}
			else
			{
				if (simon->getPositionX() * 2 < Camera::getInstance()->cameraX)
					Camera::getInstance()->setCamX(Camera::getInstance()->cameraX - 3);
				else
					setState(Midle);
			}
			break;
		case Midle:
		{
			CObject* temp = (CObject*)simon;
			swept->CheckCollision(temp->_box, _box);
			if (swept->direc != SweptAABB::Direction::None)
			{
				simon->autoWalking = true;
				simon->setactionState(SimonBelmont::ActionState::Walking);
				simon->autoRun();
			}
			else
			{
				simon->autoWalking = false;
				simon->setactionState(SimonBelmont::ActionState::Standing);
				setState(Close);
			}
		}
			break;
		case Close:
			if (getCurrentFrame() == DOOR_NORMAL)
			{
				if (getFlipX())
				{
					if (_x + _width <= Camera::getInstance()->cameraX + Camera::getInstance()->width / 2)
					{
						Camera::getInstance()->setCamX(Camera::getInstance()->cameraX - 3);
					}
					else
					{
						Stage::getInstance()->stage += 1;
						Stage::getInstance()->prePointX = simon->getPositionX();
						Stage::getInstance()->prePointY = simon->getPositionY();
						Stage::getInstance()->flip = simon->getFlipX();
						setState(End);
					}
				}
				else
				{
					if (_x >= Camera::getInstance()->cameraX - Camera::getInstance()->width / 2)
					{
						Camera::getInstance()->setCamX(Camera::getInstance()->cameraX + 3);
					}
					else
					{
						Stage::getInstance()->flip = simon->getFlipX();
						Stage::getInstance()->stage += 1;
						Stage::getInstance()->prePointX = simon->getPositionX();
						Stage::getInstance()->prePointY = simon->getPositionY();
						setState(End);
					}
				}
				
			}
			break;
		case End:
		{
			Camera::getInstance()->changeState = false;
			if (simon->getPositionX() * 2 < _x)
			{
				if (simon->getPositionX() * 2 > (_x + _width) - Camera::getInstance()->width / 2)
				{
					Camera::getInstance()->setCamX(_x + _width - Camera::getInstance()->width / 2);
					Camera::getInstance()->setCam = true;
				}
			}
			else
				if (simon->getPositionX() * 2 >= _x)
				{
					if (simon->getPositionX() * 2 < _x + Camera::getInstance()->width / 2)
					{
						Camera::getInstance()->setCamX(_x + Camera::getInstance()->width / 2);
						Camera::getInstance()->setCam = true;
					}
				}
		}
			break;
		default:
			break;
		}
	}
}

void Door::updateInfo()
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_width = getSize().width * 2;
	_height = getSize().height * 2;
	_box.x = _x;
	_box.y = _y;
	_box.h = _height;
	_box.w = _width;
}

void Door::updatePosition()
{
	switch (getState())
	{
	case Begin:
		break;
	case Open:
		if (getFlipX())
			setPositionX(defaultX/2 - 16);
		break;
	case Midle:
		break;
	case Close:
		if (getNextFrame() == DOOR_NORMAL)
			setPositionX(defaultX/2);
		break;
	case End:
		break;
	}
}

void Door::updateState(int deltaTime)
{
	switch (getState())
	{
	case DoorState::Begin:
		break;
	case DoorState::Open:
		break;
	case DoorState::Midle:
		break;
	case DoorState::Close:
		remainingChangeStateTime -= deltaTime;
		if (remainingChangeStateTime <= 0)
			setState(End);
		break;
	case DoorState::End:
		setPositionX(defaultX/2);
		break;
	}
}


