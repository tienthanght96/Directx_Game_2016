#include "WhiteSkeleton.h"
#include "Camera.h"
#include "Whip.h"

WhiteSkeleton::WhiteSkeleton(int X, int Y, int item) : CObject(22, X, Y, WHITE_SKELETON_WIDTH, WHITE_SKELETON_HEIGHT, item)
{
	initWithTexture(WHITE_SKELETON_SHEET);
	setCurrentFrame(WHITE_SKELETON_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	velocityY = 0;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	isMovement = true;
}

void WhiteSkeleton::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(_box, boxCam))
	{
		updateState(DeltaTime);

		updateFrame(DeltaTime);

		updateAD();

		updatePosition(DeltaTime);

		updateGettingDamagedTime(DeltaTime);

		updateInfo();

		updateListWepon();
	}
}

bool WhiteSkeleton::updateCollis(CObject * Ob)
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
						velocityY = 0;
						if (inRange() == true)
						{
							Shoot(swept->delta);
							if (AD == AttackDirection::Left)
								velocityX = WHITE_SKELETON_WALKING_SPEED;
							else
								velocityX = -WHITE_SKELETON_WALKING_SPEED;
						}
						else
						{
							if ((_x + _width) > (Ob->_x + Ob->_width ))
							{
								if (velocityX > 0)
									velocityY = -WHITE_SKELETON_JUMPING_SPEED;
							}
							else
								if (_x  < Ob->_x)
								{
									if (velocityX < 0)
										velocityY = -WHITE_SKELETON_JUMPING_SPEED;
								}
						}
					}
				}
				break;
				case SweptAABB::Direction::Top:
					break;
				case SweptAABB::Direction::Left:
				{
					velocityX = WHITE_SKELETON_WALKING_SPEED;
				}
				break;
				case SweptAABB::Direction::Right:
				{
					velocityX = -WHITE_SKELETON_WALKING_SPEED;
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

void WhiteSkeleton::Draw()
{
	M2DXAnimatedSprite::draw();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int WhiteSkeleton::getAnimateRate()
{
	return WHITE_SKELETON_DEFAULT_ANIMATE_RATE;
}

string WhiteSkeleton::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == WHITE_SKELETON_FRAME_1 || currentFrame == "")
			return WHITE_SKELETON_FRAME_2;
		else
			return WHITE_SKELETON_FRAME_1;
		break;
	case State::before_dead:
		return BEFORE_DEAD;
		break;
	case State::dead:
		return "";
		break;
	}
}

void WhiteSkeleton::Shoot(int deltaTime)
{
	remainingTimeToShoot -= deltaTime;
	if (remainingTimeToShoot <= 0 && getCurrentState() == alive)
	{
		if (AD == Left)
		{
			BulletManager::getInstance()->AddElement(new WhiteBone(_x / 2, (_y) / 2 + 6, AttackDirection::Left));
		}
		else
			BulletManager::getInstance()->AddElement(new WhiteBone(_x / 2 + WHITE_SKELETON_WIDTH / 2, (_y) / 2 + 6, AttackDirection::Right));
		isShooting = true;
		remainingTimeToShoot = TIME_TO_SHOOT;
	}
}

bool WhiteSkeleton::inRange()
{
	if(std::abs(_x-simonPointX) < 100)
	return true;
	return false;
}

bool WhiteSkeleton::isExist(CObject * Ob)
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

bool WhiteSkeleton::isExist(CObject * Ob, list<CObject*> listOb)
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

void WhiteSkeleton::updateListWepon()
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

void WhiteSkeleton::updateInfo()
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

void WhiteSkeleton::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		if (isShooting == false)
		{
			velocityY += GRAVITY * deltaTime;
			auto positionX = getPositionX();
			auto positionY = getPositionY();
			positionX += velocityX * deltaTime;
			positionY += velocityY * deltaTime;
			setPositionX(positionX);
			setPositionY(positionY);
		}
		else
		{
			isShooting = false;
		}
	}
}

void WhiteSkeleton::updateAD()
{
	if (currentState == alive)
	{
		if (AD == AttackDirection::Left)
			setFlipX(true);
		else
			setFlipX(false);
		if (_x < Camera::getInstance()->getBound().left)
			velocityX = WHITE_SKELETON_WALKING_SPEED;
		if (_x + _width > Camera::getInstance()->getBound().right)
			velocityX = -WHITE_SKELETON_WALKING_SPEED;
	}
}

void WhiteSkeleton::updateState(int deltaTime)
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

void WhiteSkeleton::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


