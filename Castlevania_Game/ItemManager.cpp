#include "ItemManager.h"
#include "BloodManager.h"
#include "MagicalCrytal.h"
#include "Camera.h"

ItemManager*	ItemManager::_instance = 0;

ItemManager*	ItemManager::getInstance()
{
	if (!_instance)
	{
		_instance = new ItemManager();
	}
	return _instance;
}

void ItemManager::AddElement(CObject* object)
{
	m_ListItem.push_back(object);
}

void ItemManager::Update(int deltaTime)
{
	if (BloodManager::getInstance()->bloodEnemy <= 0 && isAdded == false)
	{
		AddElement(new MagicalCrytal(Camera::getInstance()->BossX/2,Camera::getInstance()->BossY/2));
		isAdded = true;
	}
	if (m_ListItem.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end(); )
		{
			if ((*i)->isDead == true)
			{
				SAFE_DELETE(*i);
				i = m_ListItem.erase(i);
			}
			else
			{
				(*i)->Update(deltaTime);
				i++;
			}
			
		}
	}
}

void ItemManager::UpdateCollision(CObject* checkingObject)
{
	if (m_ListItem.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end();i++)
		{
			(*i)->updateCollis(checkingObject);
		}
	}
}

void ItemManager::Render()
{
	if (m_ListItem.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end(); i++)
		{
			(*i)->Draw();
		}
	}
}

void ItemManager::Release()
{
	for (list<CObject*>::iterator i = m_ListItem.begin(); i != m_ListItem.end(); i++)
	{
		SAFE_DELETE(*i);
	}
	isAdded = false;
	m_ListItem.clear();
}