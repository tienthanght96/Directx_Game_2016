#include "m2dxicollidable.h"

M2DXICollidable::M2DXICollidable() { }

M2DXICollidable::~M2DXICollidable() { }

M2DXICollidable::M2DXCollisionDirection M2DXICollidable::aabbCollideWith(M2DXICollidable* collidableObject)
{
	auto thisBoundingBox = getBoundingBox();
	auto objectBoundingBox = collidableObject->getBoundingBox();

	auto left = objectBoundingBox.left - thisBoundingBox.right;
	auto right = objectBoundingBox.right - thisBoundingBox.left;
	auto top = objectBoundingBox.top - thisBoundingBox.bottom;
	auto bottom = objectBoundingBox.bottom - thisBoundingBox.top;

	if (left > 0 || right < 0 || top > 0 || bottom < 0)
	{
		return None;
	}

	left = abs(left);
	right = abs(right);
	top = abs(top);
	bottom = abs(bottom);

	auto result = min(left, min(right, min(top, bottom)));

	if (result == left)
	{
		return Left;
	}
	else if (result == right)
	{
		return Right;
	}
	else if (result == top)
	{
		return Top;
	}
	else
	{
		return Bottom;
	}
}

M2DXICollidable::M2DXCollisionInformation M2DXICollidable::sweptAABBCollideWith(M2DXICollidable* colliableObject)
{
	auto thisBoundingBox = getBoundingBox();
	auto objectBoundingBox = colliableObject->getBoundingBox();

	M2DXCollisionInformation result;

	auto thisBroadPhaseBox = getBroadPhaseBox();
	if (thisBroadPhaseBox.intersectWith(objectBoundingBox))
	{
		auto thisVelocity = getVelocity();

		float xInvEntry, xInvExit, yInvEntry, yInvExit;
		if (thisVelocity.x > 0)
		{
			xInvEntry = objectBoundingBox.left - thisBoundingBox.right;
			xInvExit = objectBoundingBox.right - thisBoundingBox.left;
		}
		else
		{
			xInvEntry = objectBoundingBox.right - thisBoundingBox.left;
			xInvExit = objectBoundingBox.left - thisBoundingBox.right;
		}
		if (thisVelocity.y > 0)
		{
			yInvEntry = objectBoundingBox.top - thisBoundingBox.bottom;
			yInvExit = objectBoundingBox.bottom - thisBoundingBox.top;
		}
		else
		{
			yInvEntry = objectBoundingBox.bottom - thisBoundingBox.top;
			yInvExit = objectBoundingBox.top - thisBoundingBox.bottom;
		}

		float xEntry, xExit, yEntry, yExit;
		if (thisVelocity.x == 0)
		{
			xEntry = -numeric_limits<float>::infinity();
			xExit = numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / thisVelocity.x;
			xExit = xInvExit / thisVelocity.x;
		}
		if (thisVelocity.y == 0)
		{
			yEntry = -numeric_limits<float>::infinity();
			yExit = numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / thisVelocity.y;
			yExit = yInvExit / thisVelocity.y;
		}

		// Find the earliest/latest times of collision.
		auto entryTime = max(xEntry, yEntry);
		auto exitTime = min(xExit, yExit);

		// If there was no collision
		if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
		{
			return result;
		}
		else // If there was a collision
		{
			// Calculate normal of collided surface.
			if (xEntry > yEntry)
			{
				if (xInvEntry < 0.0f)
					result.collisionDirection = Right;
				else
					result.collisionDirection = Left;
			}
			else
			{
				if (yInvEntry < 0.0f)
					result.collisionDirection = Bottom;
				else
					result.collisionDirection = Top;
			}

			result.collisionTime = entryTime;
		}
	}

	return result;
}

M2DXRectangle M2DXICollidable::getBroadPhaseBox()
{
	auto velocity = getVelocity();
	auto boundingBox = getBoundingBox();

	M2DXRectangle broadPhaseBox;
	broadPhaseBox.left = velocity.x > 0 ? boundingBox.left : boundingBox.left + velocity.x;
	broadPhaseBox.top = velocity.y > 0 ? boundingBox.top : boundingBox.top + velocity.y;
	broadPhaseBox.right = velocity.x > 0 ? boundingBox.right + velocity.x : boundingBox.right;
	broadPhaseBox.bottom = velocity.y > 0 ? boundingBox.bottom + velocity.y : boundingBox.bottom;

	return broadPhaseBox;
}
