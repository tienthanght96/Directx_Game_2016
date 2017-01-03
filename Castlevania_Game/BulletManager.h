#ifndef __BULLET_MANAGER_H__
#define __BULLET_MANAGER_H__
#include "CObject.h"
#include "m2dxanimatedsprite.h"
#include "SweptAABB.h"
#include <list>
using namespace std;


class BulletManager
{
private:
	BulletManager() {}
	~BulletManager() {}
	static BulletManager*		_instance;
	list<CObject*>		m_ListBullet;
	SweptAABB *swept = new SweptAABB();
public:
	static BulletManager*	getInstance();
	void AddElement(CObject* objectWeaponry);
	void UpdateCollision(CObject* checkingObject);
	void Update(int deltaTime);
	void Render();
	void Release();
};

#endif