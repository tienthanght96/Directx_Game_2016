#include "WeponsItem.h"
#include "SimonBelmont.h"
#include "GetWepon.h"


WeponsItem::WeponsItem(int ID,int X, int Y) : CObject(ID, X, Y, WEPONS_ITEM_WIDTH, WEPONS_ITEM_HEIGHT, 0)
{
	_vy = WEPONS_ITEM_Y;
	switch (ID)
	{
	case 40:
	{
		initWithTexture(AXE_ITEM_SPRITE);
	}
		break;
	case 41:
	{
		initWithTexture(BOOMERANG_ITEM_SPRITE);
	}
	break;
	case 42:
	{
		initWithTexture(DAGGER_ITEM_SPRITE);
	}
	break;
	case 43:
	{
		initWithTexture(FIREBOMB_ITEM_SPRITE);
	}
	break;
	case 44:
	{
		initWithTexture(WATCH_ITEM_SPRITE);
	}
	break;
	}
	setPosition(M2DXPoint(_x / 2, _y / 2));
}

void WeponsItem::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
}

bool WeponsItem::updateCollis(CObject * Ob)
{
	if (!isDead)
	{
		swept->CheckCollision(_box, Ob->_box);
		if (swept->direc != SweptAABB::Direction::None)
		{
			switch (Ob->_type)
			{
			case 2:
			{
				if (swept->direc == SweptAABB::Direction::Bottom)
				{
					setPositionY(Ob->_box.y / 2 - _box.h / 2);
					_vy = 0;
				}
			}
			break;
			case 1:
			{
				isDead = true;
				SimonBelmont* temp = (SimonBelmont*)Ob;
				M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\collectitem"));
				switch (_type)
				{
				case 40:
				{
					temp->setCurrentWepons(SimonBelmont::SimonBelmontWeaponType::SimonBelmontAxe);
					GetWepon::getInstance()->wepon = 1;
				}
					break;
				case 41:
				{
					temp->setCurrentWepons(SimonBelmont::SimonBelmontWeaponType::SimonBelmontBomerang);
					GetWepon::getInstance()->wepon = 2;
				}
					break;
				case 42:
				{
					temp->setCurrentWepons(SimonBelmont::SimonBelmontWeaponType::SimonBelmontDagger);
					GetWepon::getInstance()->wepon = 4;
				}
					break;
				case 43:
				{
					temp->setCurrentWepons(SimonBelmont::SimonBelmontWeaponType::SimonBelmontHolyWater);
					GetWepon::getInstance()->wepon = 3;
				}
					break;
				case 44:
				{
					temp->setCurrentWepons(SimonBelmont::SimonBelmontWeaponType::SimonBelmontWatch);
					GetWepon::getInstance()->wepon = 5;
				}
					break;
				default:
					break;
				};
			}
			break;
			}
		}
	}
	return false;
}

void WeponsItem::updateState(int deltaTime)
{
	remainingDead -= deltaTime;
	if (remainingDead <= 0)
	{
		currentState = State::dead;
		isDead = true;
	}
}

void WeponsItem::updatePosition(int deltaTime)
{
	auto positionY = getPositionY() + _vy * deltaTime;
	setPositionY(positionY);
}

void WeponsItem::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void WeponsItem::Draw()
{
	M2DXBaseSprite::draw();
}