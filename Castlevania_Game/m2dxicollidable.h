#pragma once

#include "m2dxutil.h"

class M2DXICollidable
{
public:
	enum M2DXCollisionDirection
	{
		None,
		Left,
		Top,
		Right,
		Bottom
	};

	struct M2DXCollisionInformation
	{
		M2DXCollisionDirection collisionDirection;

		float collisionTime;

		M2DXCollisionInformation() : collisionDirection(None), collisionTime(1.0f) { }
	};

	~M2DXICollidable();

	virtual M2DXCollisionInformation collideWith(M2DXICollidable* colliableObject) = 0;

	virtual void onCollideWith(M2DXICollidable* colliableObject, M2DXCollisionInformation collisionInformation) = 0;

protected:
	M2DXICollidable();

	M2DXCollisionDirection aabbCollideWith(M2DXICollidable* colliableObject);

	virtual M2DXRectangle getBoundingBox() = 0;

	M2DXCollisionInformation sweptAABBCollideWith(M2DXICollidable* colliableObject);

	virtual D3DXVECTOR2 getVelocity() = 0;

private:
	M2DXRectangle getBroadPhaseBox();
};
