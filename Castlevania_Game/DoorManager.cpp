#include "DoorManager.h"

DoorManager*	DoorManager::_instance = 0;

void DoorManager::setListDoor(int level)
{
	auto temp = doorManager[level];
	m_ListDoor.clear();
	m_ListDoor = temp;
}

DoorManager*	DoorManager::getInstance()
{
	if (!_instance)
	{
		_instance = new DoorManager();
	}
	return _instance;
}

void DoorManager::AddElement(int level, list<Door*> temp)
{
	doorManager.insert(DoorPair(level,temp));
}

void DoorManager::Update(int deltaTime)
{
	if (m_ListDoor.empty() != true)
	{
		for (list<Door*>::iterator i = m_ListDoor.begin(); i != m_ListDoor.end(); )
		{
			(*i)->Update(deltaTime);
			i++;
		}
	}
}

void DoorManager::updateCamera(SimonBelmont * simon)
{
	if (m_ListDoor.empty() != true)
	{
		for (list<Door*>::iterator i = m_ListDoor.begin(); i != m_ListDoor.end();)
		{
			(*i)->updateCamera(simon);
			i++;
		}
	}
}

void DoorManager::UpdateCollision(CObject* checkingObject)
{
	if (m_ListDoor.empty() != true)
	{
		for (list<Door*>::iterator i = m_ListDoor.begin(); i != m_ListDoor.end();)
		{
			(*i)->updateCollis(checkingObject);
			i++;
		}
	}
}

void DoorManager::Render()
{
	if (m_ListDoor.empty() != true)
	{
		for (list<Door*>::iterator i = m_ListDoor.begin(); i != m_ListDoor.end(); i++)
		{
			(*i)->Draw();
		}
	}
}

void DoorManager::Release()
{
	for (list<Door*>::iterator i = m_ListDoor.begin(); i != m_ListDoor.end(); i++)
	{
		SAFE_DELETE(*i);
	}
	m_ListDoor.clear();
}