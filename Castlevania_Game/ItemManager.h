#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__
#include "CObject.h"
#include "m2dxanimatedsprite.h"
#include <list>
using namespace std;


class ItemManager
{
private:
	ItemManager() {}
	~ItemManager() {}
	static ItemManager*		_instance;	
	bool isAdded = false;
public:
	list<CObject*>		m_ListItem;
	static ItemManager*	getInstance();
	void AddElement(CObject* objectWeaponry);
	void UpdateCollision(CObject* checkingObject);
	void Update(int deltaTime);
	void Render();
	void Release();
};

#endif