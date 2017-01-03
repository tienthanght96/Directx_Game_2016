#pragma once
#include "m2dx.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include "Box.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
class SweptAABB
{
public:
	enum Direction
	{
		Left,
		Right,
		Top,
		Bottom,
		None
	};
	SweptAABB();
	int delta;
    Direction direc;
	void CheckCollision(Box box1, Box box2);
	// returns true if the boxes are colliding (velocities are not used)
	bool AABBCheck(Box b1, Box b2)
	{
		return !(b1.x + b1.w <= b2.x || b1.x >= b2.x + b2.w || b1.y + b1.h <= b2.y || b1.y >= b2.y + b2.h);
	}

	// returns true if the boxes are colliding (velocities are not used)
	// moveX and moveY will return the movement the b1 must move to avoid the collision
	bool AABB(Box b1, Box b2, float& moveX, float& moveY);
	// returns a box the spans both a current box and the destination box
	Box GetSweptBroadphaseBox(Box b);
	float CSweptAABB(Box b1, Box b2, float& normalx, float& normaly);
	~SweptAABB();
};

