#include "Raven.h"
#include "Camera.h"
#include "Whip.h"

Raven::Raven(int X, int Y, int item) : CObject(23, X, Y, RAVEN_WIDTH, RAVEN_HEIGHT, item)
{
	initWithTexture(RAVEN_SHEET);
	setCurrentFrame(RAVEN_SITTING);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	velocityX = - RAVEN_FLYING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	currentActionState = ActionState::Sitting;
	isMovement = true;
}

void Raven::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(_box, boxCam))
	{			
		updateState(DeltaTime);

		updateActionState(DeltaTime);

		updateFrame(DeltaTime);

		updateAD();

		updatePosition(DeltaTime);

		updateGettingDamagedTime(DeltaTime);

		updateInfo();

		updateListWepon();
	}
}

bool Raven::updateCollis(CObject * Ob)
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

void Raven::Draw()
{
	M2DXAnimatedSprite::draw();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int Raven::getAnimateRate()
{
	return RAVEN_DEFAULT_ANIMATE_RATE;
}

string Raven::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
	{
		switch (currentActionState)
		{
		case ActionState::Flying:
			if (currentFrame == RAVEN_FRAME_1 || currentFrame == RAVEN_SITTING || currentFrame == "")
				return RAVEN_FRAME_2;
			if (currentFrame == RAVEN_FRAME_2)
				return RAVEN_FRAME_3;
			if (currentFrame == RAVEN_FRAME_3)
				return RAVEN_FRAME_4;
			if (currentFrame == RAVEN_FRAME_4)
				return RAVEN_FRAME_1;
			break;
		case ActionState::Sitting:
			return RAVEN_SITTING;
			break;
		default:
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

void Raven::updateActionState(int deltaTime)
{
	switch (currentActionState)
	{
	case ActionState::Flying:
		remainingFly -= deltaTime;
		if (remainingFly <= 0)
		{
			currentActionState = ActionState::Sitting;
			remainingSitting = SITTING_TIME;
		}
		break;
	case ActionState::Sitting:
		remainingSitting -= deltaTime;
		if (remainingSitting <= 0)
		{
			currentActionState = ActionState::Flying;
			remainingFly = FLY_TIME;
		}
		break;
	default:
		break;
	}
}

bool Raven::isExist(CObject * Ob)
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

bool Raven::isExist(CObject * Ob, list<CObject*> listOb)
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

void Raven::updateListWepon()
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

void Raven::updateInfo()
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

void Raven::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		if (currentActionState == ActionState::Flying)
		{
			auto positionX = getPositionX();
			auto positionY = getPositionY();
			positionX += velocityX * deltaTime;
			positionY += velocityY * deltaTime;
			setPositionX(positionX);
			setPositionY(positionY);
		}
	}
}

void Raven::updateAD()
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
				velocityX = -RAVEN_FLYING_SPEED;
			}
			else
			{
				setFlipX(false);
				velocityX = RAVEN_FLYING_SPEED;
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
					velocityY = RAVEN_FLYING_SPEED;
				else
					if (distanceY > 0)
						velocityY = -RAVEN_FLYING_SPEED;
			}
		}
		else
			if (distanceX == 0 && distanceY != 0)
			{
				if (distanceY < 0)
					velocityY = RAVEN_FLYING_SPEED;
				else
					if (distanceY > 0)
						velocityY = -RAVEN_FLYING_SPEED;
			}
			else
				velocityY = 0;
	}
}

void Raven::updateState(int deltaTime)
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

void Raven::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


