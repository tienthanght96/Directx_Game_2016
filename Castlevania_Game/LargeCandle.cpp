#include "LargeCandle.h"
#include "Whip.h"
#include "WeponsItem.h"

Candle::Candle(int X, int Y, int item) : CObject(12, X, Y, CANDLE_WIDTH, CANDLE_HEIGHT, item)
{
	initWithTexture(CANDLE_SHEET);
	setCurrentFrame(LARGE_CANDLE_FRAME_BEGIN);
	setPosition(M2DXPoint(_x/2, _y/2));
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
}

void Candle::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateState(DeltaTime);

	updateFrame(DeltaTime);

	updateGettingDamagedTime(DeltaTime);

	updateListWepon();
}

bool Candle::updateCollis(CObject* Ob)
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
						remainingBeforDeadTime = LARGE_CANDLE_BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
					Score::getInstance()->score += 100;
				}
			}
				break;
			case 19:
			{
				if (!isExist(Ob))
				{
					health -= 50;
					if(Ob->_vx > 0)
						gettingDamaged.setPosition(M2DXPoint(_x / 2, Ob->_y / 2));
					else
						gettingDamaged.setPosition(M2DXPoint((_x + _width) / 2, Ob->_y / 2));
					getDamaged = true;
					remainingGettingDamagedTime = GETTING_DAMAGEED_TIME;
					if (health <= 0)
					{
						setState(before_dead);
						remainingBeforDeadTime = LARGE_CANDLE_BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
					Score::getInstance()->score += 100;
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
						setState(before_dead);
						remainingBeforDeadTime = LARGE_CANDLE_BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
					Score::getInstance()->score += 100;
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
						remainingBeforDeadTime = LARGE_CANDLE_BEFORE_DEAD_TIME;
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
						Score::getInstance()->score += 100;
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

void Candle::Draw()
{
	M2DXAnimatedSprite::draw();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int Candle::getAnimateRate()
{
	return LARGE_CANDLE_DEFAULT_ANIMATE_RATE;
}

string Candle::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
		switch (currentState)
		{
		case State::alive:
			if (currentFrame == LARGE_CANDLE_FRAME_BEGIN)
				return LARGE_CANDLE_FRAME_END;
			else
			{
				return LARGE_CANDLE_FRAME_BEGIN;
			}
			break;
		case State::before_dead:
			return  LARGE_CANDLE_FRAME_BEFOR_DEAD;
			break;
		case State::dead:
			return "";
			break;
		}
}

bool Candle::isExist(CObject * Ob)
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

bool Candle::isExist(CObject * Ob, list<CObject*> listOb)
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

void Candle::updateListWepon()
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

void Candle::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}

}

void Candle::updateState(int deltaTime)
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
			ItemManager::getInstance()->AddElement(new MoneyBag700(_x / 2, ( _y) / 2));
			break;
		case 35:
			ItemManager::getInstance()->AddElement(new MoneyBag1000(_x / 2, ( _y) / 2));
			break;
		case 38:
			ItemManager::getInstance()->AddElement(new MorningStar(_x / 2, (_y) / 2));
			break;
		case 40:
			ItemManager::getInstance()->AddElement(new WeponsItem(40,_x / 2, (_y) / 2));
			break;
		case 41:
			ItemManager::getInstance()->AddElement(new WeponsItem(41,_x / 2, (_y) / 2));
			break;
		case 42:
			ItemManager::getInstance()->AddElement(new WeponsItem(42,_x / 2, (_y) / 2));
			break;
		case 43:
			ItemManager::getInstance()->AddElement(new WeponsItem(43,_x / 2, (_y) / 2));
			break;
		case 44:
			ItemManager::getInstance()->AddElement(new WeponsItem(44,_x / 2, (_y) / 2));
			break;
		case 48:
			ItemManager::getInstance()->AddElement(new Cross(_x / 2, (_y) / 2));
			break;
		case 49:
			ItemManager::getInstance()->AddElement(new Potion(_x / 2, (_y) / 2));
			break;
		}
		break;
	default:
		break;
	}
}