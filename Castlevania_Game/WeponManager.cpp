#include "WeponManager.h"

WeponManager*	WeponManager::_instance = 0;

WeponManager*	WeponManager::getInstance()
{
	if (!_instance)
	{
		_instance = new WeponManager();
	}
	return _instance;
}

void WeponManager::AddElement(CObject* object)
{
	m_ListWepon.push_back(object);
}

void WeponManager::Update(int deltaTime, CObject* simon)
{
	if (m_ListWepon.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListWepon.begin(); i != m_ListWepon.end(); )
		{
			if ((*i)->_type == 3)
			{
				Whip* temp = (Whip*)(*i);
				if (temp->usingState == Whip::WhipUsingState::None)
					i = m_ListWepon.erase(i);
				else
				{
					(*i)->Update(deltaTime, simon);
					i++;
				}
			}
			else
			{
				if((*i)->isDead == true)
					i = m_ListWepon.erase(i);
				else
				{
					(*i)->Update(deltaTime, simon);
					i++;
				}
			}
		}
	}
}

void WeponManager::updateCollis(CObject * Ob)
{
	if (m_ListWepon.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListWepon.begin(); i != m_ListWepon.end(); i++)
		{
			if ((*i)->_type == 3)
			{
				Whip* temp = (Whip*)(*i);
				if (temp->usingState == Whip::End)
					Ob->updateCollis((*i));
			}
			else
			Ob->updateCollis((*i));
		}
	}
}


void WeponManager::Render()
{
	if (m_ListWepon.empty() != true)
	{
		for (list<CObject*>::iterator i = m_ListWepon.begin(); i != m_ListWepon.end(); i++)
		{
			(*i)->Draw();
		}
	}
}

void WeponManager::Release()
{
	for (list<CObject*>::iterator i = m_ListWepon.begin(); i != m_ListWepon.end(); i++)
	{
		SAFE_DELETE(*i);
	}
	m_ListWepon.clear();
}