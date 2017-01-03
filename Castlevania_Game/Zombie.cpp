#include "Zombie.h"
#include "Camera.h"
#include "Whip.h"

Zombie::Zombie(int X, int Y, int item) : CObject(5, X, Y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, item)
{
	initWithTexture(ZOMBIE_SHEET);
	setCurrentFrame(ZOMBIE_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	velocityX = -ZOMBIE_WALKING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	isMovement = true;
}

void Zombie::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateState(DeltaTime);

	updateFrame(DeltaTime);

	updateAD();

	updatePosition(DeltaTime);

	updateGettingDamagedTime(DeltaTime);

	updateInfo();

	updateListWepon();
}

bool Zombie::updateCollis(CObject * Ob)
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
					Whip* temp = (Whip*)Ob;
					if (temp->getFlipX() == false)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					velocityX = 0;
					velocityY = 0;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					setState(before_dead);
					remainingBeforDeadTime = BEFORE_DEAD_TIME;
					Score::getInstance()->score += 100;
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
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
					setPositionY(Ob->_y / 2 - _height / 2);
					velocityY = 0;
					isFall = false;
				}
				break;
				case SweptAABB::Direction::Top:
				break;
				case SweptAABB::Direction::Left:
				{
					setFlipX(false);
					velocityX = ZOMBIE_WALKING_SPEED;
				}
				break;
				case SweptAABB::Direction::Right:
				{
					setFlipX(true);
					velocityX = -ZOMBIE_WALKING_SPEED;
				}
				break;
				}
			}
			break;
			case 19:
			{
				if (!isExist(Ob))
				{
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					velocityX = 0;
					velocityY = 0;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					setState(before_dead);
					remainingBeforDeadTime = BEFORE_DEAD_TIME;
					Score::getInstance()->score += 100;
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
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

void Zombie::Draw()
{
	M2DXAnimatedSprite::draw();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int Zombie::getAnimateRate()
{
	return ZOMBIE_DEFAULT_ANIMATE_RATE;
}

string Zombie::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == ZOMBIE_FRAME_1 || currentFrame == "")
			return ZOMBIE_FRAME_2;
		else return ZOMBIE_FRAME_1;
		break;
	case State::before_dead:
		return BEFORE_DEAD;
		break;
	case State::dead:
		return "";
		break;
	}
}

bool Zombie::isExist(CObject * Ob)
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

bool Zombie::isExist(CObject * Ob, list<CObject*> listOb)
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

void Zombie::updateListWepon()
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

void Zombie::updateInfo()
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

void Zombie::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		if (isFall == true)
			velocityY = velocityY + GRAVITY * deltaTime;
		auto positionX = getPositionX();
		auto positionY = getPositionY();
		positionX += velocityX * deltaTime;
		positionY += velocityY * deltaTime;
		setPositionX(positionX);
		setPositionY(positionY);
	}
}

void Zombie::updateAD()
{
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(boxCam, _box) == false)
	{
		switch (AD)
		{
		case CObject::AttackDirection::Right:
		{
			setFlipX(false);
			velocityX = ZOMBIE_WALKING_SPEED;
		}
		break;
		case CObject::AttackDirection::Left:
		{
			setFlipX(true);
			velocityX = -ZOMBIE_WALKING_SPEED;
		}
		break;
		}
	}
	else
	{
		if (_x <= 0)
		{
			setFlipX(false);
			velocityX = ZOMBIE_WALKING_SPEED;
		}
		if (_x + _width >= (Camera::getInstance()->listFlat[Camera::getInstance()->flat]->_x*2 + Camera::getInstance()->listFlat[Camera::getInstance()->flat]->_width*2))
		{
			setFlipX(true);
			velocityX = -ZOMBIE_WALKING_SPEED;
		}
	}
}

void Zombie::updateState(int deltaTime)
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

void Zombie::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


