#include "Medusa.h"
#include "Camera.h"
#include "Whip.h"

Medusa::Medusa(int X, int Y, int item) : CObject(7, X, Y, MEDUSA_WIDTH, MEDUSA_HEIGHT, item)
{
	initWithTexture(MEDUSA_SHEET);
	setCurrentFrame(MEDUSA_FRAME_1);
	defaultX = _x;
	defaultY = _y;
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	gravity = GRAVITY;
	velocityX = - MEDUSA_FLYING_SPEED;
	velocityY = MEDUSA_JUMPING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	isMovement = true;
}

void Medusa::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	if (Camera::getInstance()->flat == defaultY / 480)
	{
		updateState(DeltaTime);

		updateFrame(DeltaTime);

		updatePosition(DeltaTime);

		updateAD();

		updateGettingDamagedTime(DeltaTime);

		updateInfo();
		
		updateListWepon();
	}
}

bool Medusa::updateCollis(CObject * Ob)
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
						Score::getInstance()->score += 300;
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
						Score::getInstance()->score += 300;
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
						Score::getInstance()->score += 300;
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
						Score::getInstance()->score += 300;
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

void Medusa::Draw()
{
	M2DXAnimatedSprite::draw();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int Medusa::getAnimateRate()
{
	return MEDUSA_DEFAULT_ANIMATE_RATE;
}

string Medusa::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == MEDUSA_FRAME_1 || currentFrame == "")
			return MEDUSA_FRAME_2;
		else
			return MEDUSA_FRAME_1;
		break;
	case State::before_dead:
		return BEFORE_DEAD;
		break;
	case State::dead:
		return "";
		break;
	}
}

bool Medusa::isExist(CObject * Ob)
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

bool Medusa::isExist(CObject * Ob, list<CObject*> listOb)
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

void Medusa::updateListWepon()
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

void Medusa::updateInfo()
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

void Medusa::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		if (velocityY >= -MEDUSA_JUMPING_SPEED)
			gravity = -GRAVITY;
		else
			if (velocityY <= MEDUSA_JUMPING_SPEED)
				gravity = GRAVITY;
			velocityY = velocityY + gravity * deltaTime;
		auto positionX = getPositionX();
		auto positionY = getPositionY();
		positionX += velocityX * deltaTime;
		positionY += velocityY * deltaTime;
		setPositionX(positionX);
		setPositionY(positionY);
	}
}

void Medusa::updateAD()
{
	if (currentState == alive)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		Box boxDefault(defaultX, defaultY, MEDUSA_WIDTH, MEDUSA_HEIGHT);
		swept->CheckCollision(_box, boxCam);
		if (swept->direc != SweptAABB::Direction::None)
		{
			if (getFlipX() == false)
			{
				if ((_x + _width) > (boxCam.x + boxCam.w))
				{
					if (swept->AABBCheck(boxCam, boxDefault) == false)
					{
						velocityY = MEDUSA_JUMPING_SPEED;
						setPosition(M2DXPoint(defaultX / 2, defaultY / 2));
					}
					else
					{
						setState(State::dead);
						isDead = true;
					}
				}
			}
			else
			{
				if (_x  < boxCam.x )
				{
					if (swept->AABBCheck(boxCam, boxDefault) == false)
					{
						velocityY = MEDUSA_JUMPING_SPEED;
						setPosition(M2DXPoint(defaultX / 2, defaultY / 2));
					}
					else
					{
						setState(State::dead);
						isDead = true;
					}
				}
			}
		}
		else
		{
			if (AD == AttackDirection::Left)
			{
				setFlipX(true);
				velocityX = -MEDUSA_FLYING_SPEED;
			}
			else
			{
				setFlipX(false);
				velocityX = MEDUSA_FLYING_SPEED;
			}
		}
	}
}

void Medusa::updateState(int deltaTime)
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
			ItemManager::getInstance()->AddElement(new SmallHeart(_x / 2, (_y) / 2));
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

void Medusa::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


