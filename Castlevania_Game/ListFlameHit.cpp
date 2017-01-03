#include "ListFlameHit.h"

ListFlame::ListFlame(int X, int Y)
{
	m_ListFlame.push_back(new FlameHit(X, Y, 0));
	m_ListFlame.push_back(new FlameHit(X, Y - 15, 0));
	m_ListFlame.push_back(new FlameHit(X + 8, Y, 0));
	m_ListFlame.push_back(new FlameHit(X + 8, Y - 15, 0));
	m_ListFlame.push_back(new FlameHit(X + 16, Y , 0));
	m_ListFlame.push_back(new FlameHit(X + 16, Y - 15, 0));
}

void ListFlame::Update(int deltaTime)
{
	for (list<FlameHit*>::iterator i = m_ListFlame.begin(); i != m_ListFlame.end();)
	{
		(*i)->Update(deltaTime);
		i++;
	}
}

void ListFlame::Render()
{
	for (list<FlameHit*>::iterator i = m_ListFlame.begin(); i != m_ListFlame.end();)
	{
		(*i)->Draw();
		i++;
	}
}

void ListFlame::Release()
{
	for (list<FlameHit*>::iterator i = m_ListFlame.begin(); i != m_ListFlame.end();)
	{
		SAFE_DELETE(*i);
	}
	m_ListFlame.clear();
}