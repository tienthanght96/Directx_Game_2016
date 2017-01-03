#ifndef __DOOR_MANAGER_H__
#define __DOOR_MANAGER_H__
#include "Door.h"
#include "SimonBelmont.h"
#include "m2dxanimatedsprite.h"
#include <list>
using namespace std;
typedef pair<int, list<Door*>> DoorPair;

class DoorManager
{
private:
	DoorManager() {}
	~DoorManager() {}
	static DoorManager*		_instance;
	list<Door*>		m_ListDoor;
	std::map<int, list<Door*>> doorManager;
public:
	void setListDoor(int level);
	static DoorManager*	getInstance();
	void AddElement(int i, list<Door*> temp);
	void UpdateCollision(CObject* checkingObject);
	void Update(int deltaTime);
	void updateCamera(SimonBelmont* simon);
	void Render();
	void Release();
};

#endif