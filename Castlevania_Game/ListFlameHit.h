#ifndef __LIST_FLAME_HIT_H__
#define __LIST_FLAME_HIT_H__
#include "Flamehit.h"
#include "m2dxanimatedsprite.h"
#include <list>
using namespace std;


class ListFlame
{
private:
public:
	ListFlame(int X, int Y);
	list<FlameHit*>			m_ListFlame;
	void Update(int deltaTime);
	void Render();
	void Release();
	ListFlame() {};
	~ListFlame() {};
};

#endif