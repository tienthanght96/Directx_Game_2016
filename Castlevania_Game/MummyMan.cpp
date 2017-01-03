#include "MummyMan.h"
#include "Camera.h"
#include "Whip.h"

MummyMan::MummyMan(int X, int Y, int item) : CObject(24, X, Y, MUMMY_MAN_WIDTH, MUMMY_MAN_HEIGHT, item)
{
	initWithTexture(MUMMY_MAN_SHEET);
	setCurrentFrame(MUMMY_MAN_FRAME_1);
	this->setPosition(M2DXPoint(_x / 2, _y / 2));
	setFlipX(true);
	velocityX = -MUMMY_MAN_WALKING_SPEED;
	gettingDamaged.initWithFile(GETTING_DAMAGED_SPRITE);
	setState(State::alive);
	visible = false;
	isMovement = true;
}

void MummyMan::Update(int DeltaTime)
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
			M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\map2"));
			M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Boss"));
		}
	}
}

bool MummyMan::updateCollis(CObject * Ob)
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
							BloodManager::getInstance()->bloodEnemy -= 8;
							M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
						}
						else
							M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hitcannon"));
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
						if (_x <= Ob->_x && velocityX == -MUMMY_MAN_WALKING_SPEED)
						{
							setFlipX(false);
							velocityX = MUMMY_MAN_WALKING_SPEED;
						}
						if ((_x + _width) >= (Ob->_x + Ob->_width) && velocityX == MUMMY_MAN_WALKING_SPEED)
						{
							setFlipX(true);
							velocityX = -MUMMY_MAN_WALKING_SPEED;
						}
					}
					break;
					case SweptAABB::Direction::Top:
						break;
					case SweptAABB::Direction::Left:
					{
						setFlipX(false);
						velocityX = MUMMY_MAN_WALKING_SPEED;
					}
					break;
					case SweptAABB::Direction::Right:
					{
						setFlipX(true);
						velocityX = -MUMMY_MAN_WALKING_SPEED;
					}
					break;
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
							BloodManager::getInstance()->bloodEnemy -= 8;
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
							BloodManager::getInstance()->bloodEnemy -= 8;
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
							BloodManager::getInstance()->bloodEnemy -= 8;
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

void MummyMan::Draw()
{
	M2DXAnimatedSprite::draw(color);
	if (getCurrentState() == State::before_dead)
		beforeDead->Render();
	if (getDamaged == true)
		gettingDamaged.draw();
}

int MummyMan::getAnimateRate()
{
	return MUMMY_MAN_DEFAULT_ANIMATE_RATE;
}

string MummyMan::getNextFrame()
{
	auto currentFrame = getCurrentFrame();
	switch (getCurrentState())
	{
	case State::alive:
		if (currentFrame == MUMMY_MAN_FRAME_1 || currentFrame == "")
			return MUMMY_MAN_FRAME_2;
		if (currentFrame == MUMMY_MAN_FRAME_2)
			return MUMMY_MAN_FRAME_3;
		if (currentFrame == MUMMY_MAN_FRAME_3)
			return MUMMY_MAN_FRAME_4;
		if (currentFrame == MUMMY_MAN_FRAME_4)
			return MUMMY_MAN_FRAME_1;
		break;
	case State::before_dead:
		return "";
		break;
	case State::dead:
		return "";
		break;
	}
}

void MummyMan::changeColor()
{
	remainingChangeColor -= 1;
	if (remainingChangeColor == 0)
	{
		if (R == 255 && G == 255 && B == 255)
		{
			color = D3DCOLOR_ARGB(255, 229, 70, 70);
			R = 229; G = 70; B = 70;
		}
		else
		{
			color = D3DCOLOR_ARGB(255, 255, 255, 255);
			R = 255; G = 255; B = 255;
		}
		remainingChangeColor = 2;
	}
}

void MummyMan::Shoot(int deltaTime)
{
	if (dem != 0)
	{
		remainingTimeToShoot -= deltaTime;
		color = D3DCOLOR_ARGB(255, 255, 255, 255);
		R = 255; G = 255; B = 255;
		if (remainingTimeToShoot <= 0 && getCurrentState() == alive)
		{
			remainingTimeWaiting -= deltaTime;
			changeColor();
			if (remainingTimeWaiting <= 0)
			{
				if (AD == Left)
				{
					BulletManager::getInstance()->AddElement(new Bandage(_x / 2, (_y) / 2, AttackDirection::Left));
				}
				else
					BulletManager::getInstance()->AddElement(new Bandage(_x / 2 + MUMMY_MAN_WIDTH / 2, (_y) / 2, AttackDirection::Right));
				remainingTimeToShoot = TIME_TO_SHOOT;
				remainingTimeWaiting = TIME_WAITING;
				dem--;
				if (dem == 0)
					goMid = true;
			}
		}
	}
}

void MummyMan::updateInfo()
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

bool MummyMan::isExist(CObject * Ob)
{
	if (!listWepon.empty())
	{
		for (int i = 0; i<listWepon.size();i++)
		{
			if (listWepon[i] == Ob)
				return true;
			else
				i++;
		}
	}
	return false;
}

bool MummyMan::isExist(CObject * Ob, list<CObject*> listOb)
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

void MummyMan::updateListWepon()
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

void MummyMan::updatePosition(int deltaTime)
{
	if (getCurrentState() == alive)
	{
		if (!(remainingTimeToShoot <= 0 && remainingTimeWaiting > 0))
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
}

void MummyMan::updateAD()
{
	if (currentState == State::alive)
	{
		MidScreen = Camera::getInstance()->listFlat[Camera::getInstance()->flat]->_x + Camera::getInstance()->listFlat[Camera::getInstance()->flat]->_width - 128;
		if (goMid == true)
		{
			color = D3DXCOLOR(255,255,255,255);
			if (_x < MidScreen*2)
			{
				velocityX = MUMMY_MAN_WALKING_SPEED;
				setFlipX(false);
			}
			else
			{
				velocityX = -MUMMY_MAN_WALKING_SPEED;
				setFlipX(true);
			}
			if ((velocityX < 0 && _x <= MidScreen*2) || (velocityX > 0 && _x >= MidScreen*2))
			{
				dem = 2;
				goMid = false;
			}
		}
		else
		{
			if (AD == AttackDirection::Left)
			{
				velocityX = -MUMMY_MAN_WALKING_SPEED;
				setFlipX(true);
			}
			else
			{
				velocityX = MUMMY_MAN_WALKING_SPEED;
				setFlipX(false);
			}
		}
	}
}

void MummyMan::updateState(int deltaTime)
{
	switch (currentState)
	{
	case State::alive:
		break;
	case State::before_dead:
		beforeDead->Update(deltaTime);
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

void MummyMan::updateGettingDamagedTime(int deltaTime)
{
	if (getDamaged == true)
	{
		remainingGettingDamagedTime -= deltaTime;
		if (remainingGettingDamagedTime <= 0)
			getDamaged = false;
	}
}


