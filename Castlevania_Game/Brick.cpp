#include "Brick.h"
#include "HolyWater.h"
#include <stdio.h>

Brick::Brick(int X, int Y, int W, int H, int item) : CObject(2 ,X ,Y ,W * 2 ,H * 2, item)
{
	isMovement = false;
	setState(State::alive);
}

void Brick::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
}

bool Brick::updateCollis(CObject * Ob)
{
	swept->CheckCollision(Ob->_box, _box);
	if (swept->direc != SweptAABB::Direction::None)
	{
		switch (Ob->_type)
		{
			case 20:
			{
				if (Ob->getCurrentState() == State::alive)
					Ob->setState(State::before_dead);
				HolyWater* tempHolywater = (HolyWater*)Ob;
				if (swept->direc == SweptAABB::Direction::Bottom)
				tempHolywater->setPositionY(_y/2 - tempHolywater->getSize().height);
			}
			break;
		}
		return true;
	}
	else
		return false;
}

void Brick::Render()
{

}
void Brick::Draw()
{
	/*brick.draw();*/
}
Brick::Brick() :CObject()
{

}
Brick::~Brick()
{

}