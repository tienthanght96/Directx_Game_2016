#include "Hunchback.h"
#include "Camera.h"
#include "Whip.h"

Hunchback::Hunchback(int X, int Y, int item) : CObject(21, X, Y, HUNCHBACK_WIDTH, HUNCHBACK_HEIGHT, item)
{
	initWithTexture(HUNCHBACK_SHEET);
	setCurrentFrame(HUNCHBACK_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	velocityX = HUNCHBACK_WALKING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	isMovement = true;
}

void Hunchback::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(_box, boxCam))
	{
		updateState(DeltaTime);

		updateFrame(DeltaTime);

		if (remainingJump > 0)
		{
			remainingJump -= DeltaTime;
			updateAD();
		}
		else
		{
			updatePosition(DeltaTime);
		}

		updateGettingDamagedTime(DeltaTime);

		updateInfo();

		updateListWepon();
	}
}

bool Hunchback::updateCollis(CObject * Ob)
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
			case 2:
			{
				switch (swept->direc)
				{
				case SweptAABB::Direction::Bottom:
				{
					if (velocityY > 0)
					{
						setPositionY(Ob->_y / 2 - _height / 2);
						if (isJumpHight == true)
						{
							velocityY = HUNCHBACK_JUMPING_SPEED;
							canChangeDirec = true;
							isJumpHight = false;
						}
						else
						{
							velocityY = HUNCHBACK_JUMPING_SPEED / 2;
							if (canChangeDirec == true)
							{
								if (AD == AttackDirection::Left)
								{
									setFlipX(true);
									velocityX = -HUNCHBACK_WALKING_SPEED;
								}
								else
								{
									setFlipX(false);
									velocityX = HUNCHBACK_WALKING_SPEED;
								}
								canChangeDirec = false;
							}
						}
					}
				}
				break;
				case SweptAABB::Direction::Top:
					break;
				case SweptAABB::Direction::Left:
				{
					setFlipX(false);
					velocityX = HUNCHBACK_WALKING_SPEED;
					isJumpHight = true;
				}
				break;
				case SweptAABB::Direction::Right:
				{
					setFlipX(true);
					velocityX = -HUNCHBACK_WALKING_SPEED;
					isJumpHight = true;
				}
				break;
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

void Hunchback::Draw()
{
		M2DXAnimatedSprite::draw();
		if (getDamaged == true)
			gettingDamaged.draw();
}

int Hunchback::getAnimateRate()
{
	return HUNCHBACK_DEFAULT_ANIMATE_RATE;
}

string Hunchback::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == HUNCHBACK_FRAME_1 || currentFrame == "")
			return HUNCHBACK_FRAME_2;
		else
			return HUNCHBACK_FRAME_1;
		break;
	case State::before_dead:
		return BEFORE_DEAD;
		break;
	case State::dead:
		return "";
		break;
	}
}

bool Hunchback::isExist(CObject * Ob)
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

bool Hunchback::isExist(CObject * Ob, list<CObject*> listOb)
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

void Hunchback::updateListWepon()
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

void Hunchback::updateInfo()
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

void Hunchback::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		velocityY += GRAVITY * deltaTime;
		auto positionX = getPositionX();
		auto positionY = getPositionY();
		positionX += velocityX * deltaTime;
		positionY += velocityY * deltaTime;
		setPositionX(positionX);
		setPositionY(positionY);
	}
}

void Hunchback::updateAD()
{
	if (currentState == alive)
	{
		if (AD == AttackDirection::Left)
			setFlipX(true);
		else
			setFlipX(false);
	}
}

void Hunchback::updateState(int deltaTime)
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

void Hunchback::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


