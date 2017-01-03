#ifndef __WEPON_MANAGER_H__
#define __WEPON_MANAGER_H__
#include "CObject.h"
#include "m2dxanimatedsprite.h"
#include "SimonBelmont.h"
#include "Whip.h"
#include <list>
using namespace std;


class WeponManager
{
private:
	WeponManager() {}
	~WeponManager() {}
	static WeponManager*		_instance;

public:
	list<CObject*>		m_ListWepon;
	static WeponManager*	getInstance();
	void AddElement(CObject* objectWeaponry);
	void Update(int deltaTime, CObject* simon);
	void updateCollis(CObject* Ob);
	void Render();
	void Release();
};

#endif