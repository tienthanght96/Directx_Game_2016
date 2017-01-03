#include "BulletManager.h"
#include "Camera.h"

BulletManager*	BulletManager::_instance = 0;

BulletManager*	BulletManager::getInstance()
{
	if (!_instance)
	{
		_instance = new BulletManager();
	}
	return _instance;
}

void BulletManager::AddElement(CObject* object)
{
	m_ListBullet.push_back(object);
}

void BulletManager::Update(int deltaTime)
{
	if (m_ListBullet.empty() != true)
	{
		RECT viewPort(Camera::getInstance()->getBound());
		Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
		for (list<CObject*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end(); )
		{
			(*i)->Update(deltaTime);
			if (swept->AABBCheck(boxCam, (*i)->_box) == false)
			{
				SAFE_DELETE(*i);
				i = m_ListBullet.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

void BulletManager::UpdateCollision(CObject* checkingObject)
{
	if (m_ListBullet.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end();)
		{
			(*i)->updateCollis(checkingObject);

			if ((*i)->isDead == true)
			{
				SAFE_DELETE(*i);
				i = m_ListBullet.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

void BulletManager::Render()
{
	if (m_ListBullet.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end(); i++)
		{
			(*i)->Draw();
		}
	}
}

void BulletManager::Release()
{
	for (list<CObject*>::iterator i = m_ListBullet.begin(); i != m_ListBullet.end(); i++)
	{
		SAFE_DELETE(*i);
	}
	m_ListBullet.clear();
}