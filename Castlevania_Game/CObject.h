#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Box.h"
#include "Global.h"
#include "Score.h"

#define GETTING_DAMAGED_SPRITE "Resources\\Sprites\\GettingDamaged.png"
#define GETTING_DAMAGEED_TIME 150

class CObject {
protected:

public:
	
	enum State
	{
		alive,
		before_dead,
		dead
	};
	enum AttackDirection
	{
		Left,
		Right
	};
	bool isMovement = false;
	int _x;
	int _y;
	int _width;
	int _height;
	int _item;
	float _vx;
	float _vy;
	float _gravity;
	bool canDamaged;
	int _type;
	int simonPointX;
	int simonPointY;
	bool visible = false;
	bool attacked = false;
	void getSimonPoint(int SimonPointX, int SimonPointY) { simonPointX = SimonPointX * 2; simonPointY = SimonPointY * 2; };
	AttackDirection AD;
	void setAD(AttackDirection attackDirection) { AD = attackDirection; };
	RECT _bound;
	Box _box;
	State currentState;
	bool isFall = true;
	inline State getCurrentState() { return currentState; };
	inline void setState(State nextState) { currentState = nextState; };
	bool isDead = false;
	virtual bool updateCollis(CObject* Ob) { return false; };
	float pointX;
	float pointY;
	CObject::CObject(int type, int x, int y, int width, int height, int item);
	virtual void Update(int deltatime) {}
	virtual void Update(int deltatime, CObject* simon) {}
	virtual void Draw() {}
	virtual void ChangeState(int state) {}
	virtual void Restore() {}

	
	CObject() ;
	void Release() {};
	void UpdatePosition(int time);
	


	~CObject();
};

#endif