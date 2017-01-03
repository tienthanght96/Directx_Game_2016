#include "Ghost.h"
#include "Camera.h"
#include "Whip.h"

Ghost::Ghost(int X, int Y, int item) : CObject(6, X, Y, GHOST_WIDTH, GHOST_HEIGHT, item)
{
	initWithTexture(GHOST_SHEET);
	setCurrentFrame(GHOST_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	velocityX = -GHOST_FLYING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	isMovement = true;
}

void Ghost::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	if (visible == false)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		swept->CheckCollision(boxCam, _box);
		if (swept->AABBCheck(_box, boxCam))
		{
			if (inRange = false)
			{
				if (std::abs(_x - simonPointX) <= 25 && std::abs(_y - simonPointY) <= 25)
				{
					inRange = true;
					dem++;
				}
			}
			else
			{
				if (swept->direc == SweptAABB::Direction::Left)
				{
					if (_x <= boxCam.x)
					{
						dem ++;
					}
				}
				else
					if ( (_x + _width) >= (boxCam.x + boxCam.w) && swept->direc == SweptAABB::Direction::Right )
					{
						dem++;
					}
			}
			if (dem == 2)
				visible = true;
		}
	}
	else
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

bool Ghost::updateCollis(CObject * Ob)
{
	if (!isDead && currentState == alive )
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
					else
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hitcannon"));
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
					else
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hitcannon"));
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
						setState(before_dead);
						remainingBeforDeadTime = BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
					Score::getInstance()->score += 300;
				}
			}
			break;
			}
			return true;
		}
	}
	return false;
}

void Ghost::Draw()
{
	if (visible == true)
	{
		M2DXAnimatedSprite::draw();
		if (getDamaged == true)
			gettingDamaged.draw();
	}
}

int Ghost::getAnimateRate()
{
	return GHOST_DEFAULT_ANIMATE_RATE;
}

string Ghost::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == GHOST_FRAME_1 || currentFrame == "")
			return GHOST_FRAME_2;
		else
			return GHOST_FRAME_1;
		break;
	case State::before_dead:
		return BEFORE_DEAD;
		break;
	case State::dead:
		return "";
		break;
	}
}

bool Ghost::isExist(CObject * Ob)
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

bool Ghost::isExist(CObject * Ob, list<CObject*> listOb)
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

void Ghost::updateListWepon()
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

void Ghost::updateInfo()
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

void Ghost::updatePosition(int deltaTime)
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

void Ghost::updateAD()
{
	if (currentState == alive)
	{
		float distanceX = _x - simonPointX;
		float distanceY = _y - simonPointY;
		if (distanceX != 0)
		{
			if (AD == AttackDirection::Left)
			{
				setFlipX(true);
				velocityX = -GHOST_FLYING_SPEED;
			}
			else
			{
				setFlipX(false);
				velocityX = GHOST_FLYING_SPEED;
			}
		}
		else
			velocityX = 0;

		if (distanceY != 0 && distanceX != 0)
		{
			velocityY = (distanceY / distanceX) * velocityX;
			if (abs(velocityY) > 2 * abs(velocityX))
			{
				if (distanceY < 0)
					velocityY = GHOST_FLYING_SPEED;
				else
					if (distanceY > 0)
						velocityY = -GHOST_FLYING_SPEED;
			}
		}
		else
			if (distanceX == 0 && distanceY != 0)
			{
				if (distanceY < 0)
					velocityY = GHOST_FLYING_SPEED;
				else
					if (distanceY > 0)
						velocityY = - GHOST_FLYING_SPEED;
			}
			else
				velocityY = 0;
	}
}

void Ghost::updateState(int deltaTime)
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
			ItemManager::getInstance()->AddElement(new LargeHeart(_x / 2, ( _y) / 2));
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
			ItemManager::getInstance()->AddElement(new MoneyBag1000(_x / 2, ( _y) / 2));
			break;
		}
		break;
	default:
		break;
	}
}

void Ghost::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


