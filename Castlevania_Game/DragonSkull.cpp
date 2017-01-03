#include "DragonSkull.h"
#include "Camera.h"
#include "Whip.h"

DragonSkull::DragonSkull(int X, int Y, int item) : CObject(11, X, Y, DRAGON_SKULL_WIDTH, DRAGON_SKULL_HEIGHT, item)
{
	initWithTexture(DRAGON_SKULL_SHEET);
	setCurrentFrame(DRAGON_SKULL);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	remainingTimeToShoot = 0;
	isMovement = false;
}

void DragonSkull::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateState(DeltaTime);

	updateFrame(DeltaTime);

	updateAD();

	Shoot(DeltaTime);

	updateGettingDamagedTime(DeltaTime);

	updateListWepon();
}

bool DragonSkull::updateCollis(CObject* Ob)
{
	if (!isDead && currentState == alive)
	{
		swept->CheckCollision(Ob->_box, _box);
		if (swept->direc != SweptAABB::Direction::None)
		{
			switch (Ob->_type)
			{
			case 3:
			{
				if (!isExist(Ob))
				{
					health -= 50;
					Ob->canDamaged = false;
					Whip* temp = (Whip*)Ob;
					if (temp->getFlipX() == false)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (health <= 0)
					{
						setState(before_dead);
						remainingBeforDeadTime = DRAGON_SKULL_BEFORE_DEAD_TIME;
						Score::getInstance()->score += 400;
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
					health -= 50;
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (health <= 0)
					{
						setState(before_dead);
						remainingBeforDeadTime = DRAGON_SKULL_BEFORE_DEAD_TIME;
						Score::getInstance()->score += 400;
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
					health -= 50;
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (health <= 0)
					{
						Score::getInstance()->score += 400;
						setState(before_dead);
						remainingBeforDeadTime = DRAGON_SKULL_BEFORE_DEAD_TIME;
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
					health -= 50;
					if (Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (health <= 0)
					{
						setState(before_dead);
						remainingBeforDeadTime = DRAGON_SKULL_BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
						Score::getInstance()->score += 400;
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

void DragonSkull::Draw()
{
	M2DXAnimatedSprite::draw(color);
	if (getDamaged == true)
		gettingDamaged.draw();
}

int DragonSkull::getAnimateRate()
{
	return DRAGON_SKULL_DEFAULT_ANIMATE_RATE;
}

string DragonSkull::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (currentState)
	{
	case State::alive:
		return DRAGON_SKULL;
		break;
	case State::before_dead:
		return  BEFORE_DEAD;
		break;
	case State::dead:
		return ""; 
		break;
	}
}

bool DragonSkull::isExist(CObject * Ob)
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

bool DragonSkull::isExist(CObject * Ob, list<CObject*> listOb)
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

void DragonSkull::updateListWepon()
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

void DragonSkull::Shoot(int deltaTime)
{
	remainingTimeToShoot -= deltaTime;
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	if (swept->AABBCheck(_box, boxCam))
	{
		if (remainingTimeToShoot <= 0)
		{
			if (canShoot == true)
			{
				if (getFlipX())
				{
					BulletManager::getInstance()->AddElement(new FireBall(_x / 2 - 7, (_y) / 2 + 6, AttackDirection::Left));
				}
				else
					BulletManager::getInstance()->AddElement(new FireBall(_x / 2 + DRAGON_SKULL_WIDTH / 2, (_y) / 2 + 6, AttackDirection::Right));
				dem--;
				color = D3DCOLOR_ARGB(255, 223, 0, 31);
				if (dem == 0)
					canShoot = false;
			}
			else
			{
				dem++;
				if (dem == 2)
					canShoot = true;
				color = D3DCOLOR_ARGB(255, 255, 255, 255);
			}
			remainingTimeToShoot = TIME_TO_SHOOT;
		}
	}
}

void DragonSkull::updateAD()
{
	if (currentState == alive)
	{
		if (AD == Left)
		{
			setFlipX(true);
		}
		else
			setFlipX(false);
	}
}

void DragonSkull::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}

}

void DragonSkull::updateState(int deltaTime)
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
			ItemManager::getInstance()->AddElement(new MoneyBag1000(_x / 2, (_y) / 2));
			break;
		}
		break;
	default:
		break;
	}
}