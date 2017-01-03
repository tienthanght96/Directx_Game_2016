#include "Block.h"
#include "Whip.h"
#include "PorkChop.h"
#include "Crown.h"
#include "ItemManager.h"

Block::Block(int X, int Y, int item) : CObject(37, X, Y, BLOCK_WIDTH, BLOCK_HEIGHT, item)
{
	initWithTexture("");
	setPosition(M2DXPoint(_x / 2, _y / 2));
	setState(State::alive);
	allocated = false;
}

void Block::Update(int DeltaTime)
{
	swept->delta = DeltaTime;

	updateState(DeltaTime);

	updateListWepon();
}

bool Block::updateCollis(CObject* Ob)
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
					if (health <= 0)
					{
						setState(before_dead);
						_listChunk = new ListChunk(getPositionX() + 8, getPositionY() + 8);
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
					if (health <= 0)
					{
						setState(before_dead);
						_listChunk = new ListChunk(getPositionX() + 8, getPositionY() + 8);
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
					if (health <= 0)
					{
						setState(before_dead);
						_listChunk = new ListChunk(getPositionX() + 8, getPositionY() + 8);
						M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\hit"));
					}
					listWepon.push_back(Ob);
					Score::getInstance()->score += 100;;
				}
			}
			break;
			case 26:
			{
				if (!isExist(Ob))
				{
					Ob->isDead = true;
					health -= 50;
					if (health <= 0)
					{
						setState(before_dead);
						_listChunk = new ListChunk(getPositionX() + 8, getPositionY() + 8);
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

void Block::Draw()
{
	M2DXBaseSprite::draw();
	if (currentState == State::before_dead)
		_listChunk->Render();
}


bool Block::isExist(CObject * Ob)
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

bool Block::isExist(CObject * Ob, list<CObject*> listOb)
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

void Block::updateListWepon()
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

void Block::updateState(int deltaTime)
{
	switch (currentState)
	{
	case State::alive:
		break;
	case State::before_dead:
		initWithTexture("Resources\\Sprites\\Broken");
		_listChunk->Update(deltaTime);
		if (allocated == false)
		{
			switch (_item)
			{
			case 39:
				ItemManager::getInstance()->AddElement(new PorkChop(_x / 2, (_y) / 2));
				allocated = true;
				break;
			case 45:
				if (simonPointX + 32 >= (_x + _width))
				{
					ItemManager::getInstance()->AddElement(new Crown(_x / 2 - 96, _y / 2 + 80));
					allocated = true;
				}
				break;
			default:
				break;
			}
		}
		break;
	case State::dead:
		break;
	default:
		break;
	}
}