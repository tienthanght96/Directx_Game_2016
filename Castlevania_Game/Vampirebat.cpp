#include "VampireBat.h"
#include "Camera.h"
#include "Whip.h"

VampireBat::VampireBat(int X, int Y, int item) : CObject(4, X, Y, VAMPIRE_BAT_WIDTH, VAMPIRE_BAT_HEIGHT, item)
{
	initWithTexture(VAMPIRE_BAT_SHEET);
	setActionState(Hanging);
	setCurrentFrame(VAMPIRE_BAT_HANGING);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	velocityX = 0;
	velocityY = 0;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	isMovement = true;
}

void VampireBat::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateState(DeltaTime);

	updateActionState();

	updateFrame(DeltaTime);

	updateAD();

	updatePosition(DeltaTime);

	updateGettingDamagedTime(DeltaTime);

	updateInfo();

	updateListWepon();
}

bool VampireBat::updateCollis(CObject * Ob)
{
	if (!isDead && currentState == alive)
	{
		swept->CheckCollision(_box, Ob->_box);
		if (swept->direc != SweptAABB::Direction::None)
		{
			switch (Ob->_type)
			{
			case 3:
			{
				if (!isExist(Ob))
				{
					Life -= 1;
					Ob->canDamaged = false;
					Whip* temp = (Whip*)Ob;
					if (temp->getFlipX() == false)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (Life == 0)
					{
						velocityX = 0;
						velocityY = 0;
						setState(before_dead);
						remainingBeforDeadTime = BEFORE_DEAD_TIME;
						Score::getInstance()->score += 200;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
				}
			}
			break;
			case 19:
			{
				if (!isExist(Ob))
				{
					Life -= 1;
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (Life <= 0)
					{
						setState(before_dead);
						remainingBeforDeadTime = BEFORE_DEAD_TIME;
						Score::getInstance()->score += 200;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
				}
			}
			break;
			case 20:
			{
				if (!isExist(Ob))
				{
					if (Ob->getCurrentState() == State::alive)
						Ob->setState(State::before_dead);
					Life -= 1;
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (Life <= 0)
					{
						Score::getInstance()->score += 200;
						setState(before_dead);
						remainingBeforDeadTime = BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
				}
			}
			break;
			case 26:
			{
				if (!isExist(Ob))
				{
					Ob->isDead = true;
					Life -= 1;
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (Life <= 0)
					{
						setState(before_dead);
						remainingBeforDeadTime = BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
						Score::getInstance()->score += 200;
					}
					listWepon.push_back(Ob);
				}
			}
			break;
			}
			return true;
		}
	}
	return false;
}

void VampireBat::Draw()
{
	M2DXAnimatedSprite::draw();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int VampireBat::getAnimateRate()
{
	return VAMPIRE_BAT_DEFAULT_ANIMATE_RATE;
}

string VampireBat::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
	{
		auto currentActionState = getActionState();
		switch (currentActionState)
		{
		case Hanging:
			return VAMPIRE_BAT_HANGING;
			break;
		case Flying:
		{
			if (currentFrame == VAMPIRE_BAT_FRAME_1 )
				return VAMPIRE_BAT_FRAME_2;
			if (currentFrame == VAMPIRE_BAT_FRAME_2)
				return VAMPIRE_BAT_FRAME_3;
			if (currentFrame == VAMPIRE_BAT_FRAME_3)
				return VAMPIRE_BAT_FRAME_4;
			if (currentFrame == VAMPIRE_BAT_FRAME_4 || currentFrame == VAMPIRE_BAT_HANGING)
				return VAMPIRE_BAT_FRAME_1;
		}
		break;
		}
	}
		break;
	case State::before_dead:
		return BEFORE_DEAD;
		break;
	case State::dead:
		return "";
		break;
	}
}

void VampireBat::updateActionState()
{
	if (currentState == alive && actionState == Hanging)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		if (swept->AABBCheck(_box, boxCam))
		{
			if (AD == AttackDirection::Left)
			{
				setFlipX(true);
				if ((_x - simonPointX) <= (Camera::getInstance()->width / 2) && _y <= simonPointY && (simonPointY - _y)  <= Camera::getInstance()->height / 4)
				{
					setActionState(Flying);
				}
			}
			else
			{
				setFlipX(false);
				if ((simonPointX - _x) <= (Camera::getInstance()->width / 2) && _y <= simonPointY && (simonPointY - _y)  <= Camera::getInstance()->height / 4)
				{
					setActionState(Flying);
				}
			}
		}
	}
}

bool VampireBat::isExist(CObject * Ob)
{
	if (!listWepon.empty())
	{
		for (vector<CObject*>::iterator i = listWepon.begin(); i != listWepon.end();)
		{
			if ((*i) == Ob)
				return true;
			else
				i++;
		}
	}
	return false;
}

bool VampireBat::isExist(CObject * Ob, list<CObject*> listOb)
{
	if (!listOb.empty())
	{
		for (list<CObject*>::iterator i = listOb.begin(); i != listOb.end();)
		{
			if ((*i) == Ob)
				return true;
			else
				i++;
		}
	}
	return false;
}

void VampireBat::updateListWepon()
{
	if (!listWepon.empty())
	{
		for (vector<CObject*>::iterator i = listWepon.begin(); i != listWepon.end();)
		{
			if (!isExist(*i, WeponManager::getInstance()->m_ListWepon) || ((*i)->_vx >= -0.0090820 && (*i)->_vx <= 0.0090820))
			{
				i = listWepon.erase(i);
			}
			else
				i++;
		}
	}
}

void VampireBat::updateInfo()
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_width = getSize().width * 2;
	_height = getSize().height * 2;
	_vx = velocityX;
	_vy = velocityY;
	_box.x = _x;
	_box.y = _y;
	_box.w = _width;
	_box.h = _height;
	_box.vx = _vx;
	_box.vy = _vy;
}

void VampireBat::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		auto positionX = getPositionX();
		auto positionY = getPositionY();
		positionX += velocityX * deltaTime;
		positionY += velocityY * deltaTime;
		setPositionX(positionX);
		setPositionY(positionY);
	}
}

void VampireBat::updateAD()
{
	if (currentState == alive && actionState == Flying)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		if (swept->AABBCheck(_box,boxCam))
		{
			if (_y < simonPointY)
				velocityY = VAMPIRE_BAT_FLYING_SPEED;
			else
				velocityY = 0;
			if (getFlipX() == true)
				velocityX = -VAMPIRE_BAT_FLYING_SPEED;
			else
				velocityX = VAMPIRE_BAT_FLYING_SPEED;
		}
		else
		{
			setState(dead);
			isDead = true;
		}
	}
}

void VampireBat::updateState(int deltaTime)
{
	switch (currentState)
	{
	case State::alive:
		break;
	case State::before_dead:
		remainingBeforDeadTime -= deltaTime;
		if (remainingBeforDeadTime <= 0)
		{
			setState(dead);
		}
		break;
	case State::dead:
		isDead = true;
		switch (_item)
		{
		case 30:
			ItemManager::getInstance()->AddElement(new SmallHeart(_x / 2, ( _y) / 2));
			break;
		case 31:
			ItemManager::getInstance()->AddElement(new LargeHeart(_x / 2, (_y) / 2));
			break;
		case 32:
			ItemManager::getInstance()->AddElement(new MoneyBag100(_x / 2, (_y) / 2));
			break;
		case 33:
			ItemManager::getInstance()->AddElement(new MoneyBag400(_x / 2, (_y) / 2));
			break;
		case 34:
			ItemManager::getInstance()->AddElement(new MoneyBag700(_x / 2, (_y) / 2));
			break;
		case 35:
			ItemManager::getInstance()->AddElement(new MoneyBag1000(_x / 2, (_y) / 2));
			break;
		}
		break;
	default:
		break;
	}
}

void VampireBat::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


