#include "QueenMedusa.h"
#include "Camera.h"
#include "Whip.h"
#include "BloodManager.h"

QueenMedusa::QueenMedusa(int X, int Y, int item) : CObject(13, X, Y, QUEEN_MEDUSA_WIDTH, QUEEN_MEDUSA_HEIGHT, item)
{
	initWithTexture(QUEEN_MEDUSA_SHEET);
	setCurrentFrame(QUEEN_MEDUSA_FRAME_1);
	setPosition(M2DXPoint(_x / 2, _y / 2));
	remainingTimeToAttack = 0;
	setFlipX(true);
	velocityX = -QUEEN_MEDUSA_FLYING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	visible = false;
	isMovement = true;
}

void QueenMedusa::Update(int DeltaTime)
{
	if (visible == true)
	{
		swept->delta = DeltaTime;
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		if (swept->AABBCheck(_box, boxCam))
		{
			updateState(DeltaTime);

			updateFrame(DeltaTime);

			updateActionState(DeltaTime);

			updateAD();

			Shoot(DeltaTime);

			updatePosition(DeltaTime);

			updateGettingDamagedTime(DeltaTime);

			updateInfo();

			updateListWepon();
		}
	}
	else
	{
		if (Camera::getInstance()->cameraX == Camera::getInstance()->BossX && Camera::getInstance()->cameraY == Camera::getInstance()->BossY)
		{
			visible = true;
			M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\map1"));
			M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Boss"));
		}
	}
}

bool QueenMedusa::updateCollis(CObject * Ob)
{
	if (visible == true)
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
							beforeDead = new ListFlame(_x / 2, (_y) / 2);
							remainingBeforDeadTime = BEFORE_DEAD_TIME;
							Score::getInstance()->score += 3000;
							BloodManager::getInstance()->bloodEnemy -= 16;
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
						Ob->canDamaged = false;
						if (Ob->_vx > 0)
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
							beforeDead = new ListFlame(_x / 2, (_y) / 2);
							remainingBeforDeadTime = BEFORE_DEAD_TIME;
							Score::getInstance()->score += 3000;
							BloodManager::getInstance()->bloodEnemy -= 16;
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
						Ob->canDamaged = false;
						if (Ob->_vx > 0)
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
							beforeDead = new ListFlame(_x / 2, (_y) / 2);
							remainingBeforDeadTime = BEFORE_DEAD_TIME;
							Score::getInstance()->score += 3000;
							BloodManager::getInstance()->bloodEnemy -= 16;
							M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
						}
						else
							M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hitcannon"));
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
						Ob->canDamaged = false;
						if (Ob->_vx > 0)
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
							beforeDead = new ListFlame(_x / 2, (_y) / 2);
							remainingBeforDeadTime = BEFORE_DEAD_TIME;
							Score::getInstance()->score += 3000;
							BloodManager::getInstance()->bloodEnemy -= 16;
							M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
						}
						else
							M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hitcannon"));
						listWepon.push_back(Ob);
					}
				}
				break;
				}
				return true;
			}
		}
	}
		return false;
}

void QueenMedusa::Draw()
{
	if (visible == true)
	{
		M2DXAnimatedSprite::draw();
		if (getCurrentState() == State::before_dead)
			beforeDead->Render();
		if (getDamaged == true)
			gettingDamaged.draw();
	}
}

int QueenMedusa::getAnimateRate()
{
	return QUEEN_MEDUSA_DEFAULT_ANIMATE_RATE;
}

string QueenMedusa::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == QUEEN_MEDUSA_FRAME_1 || currentFrame == "")
			return QUEEN_MEDUSA_FRAME_2;
		else
			return QUEEN_MEDUSA_FRAME_1;
		break;
	case State::before_dead:
		return "";
		break;
	case State::dead:
		return "";
		break;
	}
}

void QueenMedusa::Shoot(int deltaTime)
{
	remainingTimeToShoot -= deltaTime;
	if (remainingTimeToShoot <= 0 && getCurrentState() == alive)
	{
		if (AD == Left)
		{
			BulletManager::getInstance()->AddElement(new Snake(_x / 2, (_y) / 2, AttackDirection::Left));
		}
		else
			BulletManager::getInstance()->AddElement(new Snake(_x / 2 + QUEEN_MEDUSA_WIDTH / 2, (_y) / 2, AttackDirection::Right));
		remainingTimeToShoot = TIME_TO_SHOOT;
		remainingTimeWaiting = TIME_WAITING;
	}
}

void QueenMedusa::updateActionState(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		switch (actionState)
		{
		case ActionState::attack:
		{
			simonPointX = simonPointX;
			simonPointY = simonPointY + 48;
			if (attacked == true)
			{
				setActionState(ActionState::defense);
				attacked = false;
				remainingTimeToAttack = TIME_TO_ATTACK;
			}
		}
		break;
		case ActionState::defense:
		{
			if (AD == Left)
			{
				simonPointX += 200;
				simonPointY = simonPointY + 30;
			}
			else
			{
				simonPointX -= 200;
				simonPointY = simonPointY + 30;
			}
			remainingTimeToAttack -= deltaTime;
			if (remainingTimeToAttack <= 0)
			{
				setActionState(ActionState::attack);
			}
		}
		break;
		}
	}
}

bool QueenMedusa::isExist(CObject * Ob)
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

bool QueenMedusa::isExist(CObject * Ob, list<CObject*> listOb)
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

void QueenMedusa::updateListWepon()
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

void QueenMedusa::updateInfo()
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

void QueenMedusa::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		remainingTimeWaiting -= deltaTime;
		if (remainingTimeWaiting <= 0)
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

void QueenMedusa::updateAD()
{
	if (currentState == alive)
	{
		float distanceX = _x - simonPointX;
		float distanceY = _y - simonPointY;
		if (distanceX != 0)
		{
			if (distanceX > 0)
			{
				setFlipX(true);
				velocityX = -QUEEN_MEDUSA_FLYING_SPEED;
			}
			else
			{
				setFlipX(false);
				velocityX = QUEEN_MEDUSA_FLYING_SPEED;
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
					velocityY = QUEEN_MEDUSA_FLYING_SPEED;
				else
					if (distanceY > 0)
						velocityY = -QUEEN_MEDUSA_FLYING_SPEED;
			}
		}
		else
			if (distanceX == 0 && distanceY != 0)
			{
				if (distanceY < 0)
					velocityY = QUEEN_MEDUSA_FLYING_SPEED;
				else
					if (distanceY > 0)
						velocityY = -QUEEN_MEDUSA_FLYING_SPEED;
			}
			else
				velocityY = 0;
	}
}

void QueenMedusa::updateState(int deltaTime)
{
	switch (currentState)
	{
	case State::alive:
		break;
	case State::before_dead:
		remainingBeforDeadTime -= deltaTime;
		beforeDead->Update(deltaTime);
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
			ItemManager::getInstance()->AddElement(new MoneyBag400(_x / 2, ( _y) / 2));
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

void QueenMedusa::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


