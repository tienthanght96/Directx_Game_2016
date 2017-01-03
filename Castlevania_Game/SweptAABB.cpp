#include "SweptAABB.h"


SweptAABB::SweptAABB()
{
}

float SweptAABB::CSweptAABB(Box b1, Box b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

Box SweptAABB::GetSweptBroadphaseBox(Box b)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphasebox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphasebox.w = b.vx > 0 ? b.vx + b.w : b.w - b.vx;
	broadphasebox.h = b.vy > 0 ? b.vy + b.h : b.h - b.vy;

	return broadphasebox;
}
bool SweptAABB::AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return false;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

void SweptAABB::CheckCollision(Box box1, Box box2)
{
	float moveX, moveY;
	float normalX, normalY;
	float timeCollision;
	if (AABB(box1, box2, moveX, moveY) == false )
	{
		// Kiểm tra _Object có động hay không 
		// nếu vật nằm trong vùng không gian của đối tượng chính
		auto vel = D3DXVECTOR2(box1.vx - box2.vx, box1.vy - box2.vy);
		Box temp(box1.x,box1.y,box1.w,box1.h,vel.x * delta, vel.y * delta);
		if (AABB(GetSweptBroadphaseBox(temp), box2, moveX, moveY) == true)
		{
			timeCollision = CSweptAABB(temp, box2, normalX, normalY);

			if (timeCollision > 0.0f && timeCollision < 1.0f)
			{
				if (normalY != 0.0f)
				{
					if (moveY != 0)
					{
						if (normalY == 1.0f)
						{
							direc = Top;
							return;
						}
						else if (normalY == -1.0f)
						{
							direc = Bottom;
							return;
						}
					}
				}
				else
				{
					if (moveX != 0.0f)
					{
						if (normalX == 1.0f)
						{
							direc = Left;
							return ;
						}
						else if (normalX == -1.0f)
						{
							direc = Right;
							return ;
						}
					}
				}
			}
		}
		else
		{
			//if(CheckAABB(_AnimationObject->GetBroadPhaseBox(D3DXVECTOR2(0, -300.0f)), _Object->GetBox()))
			//{
			//	return IDDirection::DIR_TOP;
			//}
		}

	}
	else
	{
		if (moveX != 0)
		{
			//if(abs(m_MoveX) < abs(moveX))
			//{
			//}

			if (moveX < 0.0f)
			{
				direc = Right;
				return ;
			}
			else
			{
				direc = Left;
				return ;
			}
		}
		else if (moveY != 0)
		{
			//if(abs(m_MoveY) < abs(moveY))
			//{
			//}

			if (moveY >= 0.0f)
			{
				direc = Top;
				return ;
			}
			else
			{
				direc = Bottom;
				return ;
			}
		}
		else
		{
			if (((box1.y + box1.h) == box2.y && (box1.x + box1.w) == box2.x)
				|| ((box2.y + box2.h) == box1.y && (box2.x + box2.w) == box1.x))
			{
				direc = None;
				return;
			}

			if ((box1.y + box1.h) == box2.y)
			{
				//_AnimationObject->m_Position.y = _AnimationObject->m_Position.y - 1;
				//_DynamicObject->setPositionY(_DynamicObject->getPositionVec2().y- 0.1f);
				direc = Bottom;
				return;
			}
			else if ((box2.y + box2.h) == box1.y)
			{
				//_AnimationObject->m_Position.y = _AnimationObject->m_Position.y + 1;
				//_DynamicObject->setPositionY(_DynamicObject->getPositionVec2().y + 1);
				direc = Top;
				return;
			}
			else if ((box1.x + box1.w) == box2.x)
			{
				direc = Right;
				return;
			}
			else if ((box2.x + box2.w) == box1.x)
			{
				direc = Left;
				return ;
			}
		}
	}

	direc = None;
	return;
}

SweptAABB::~SweptAABB()
{
}
