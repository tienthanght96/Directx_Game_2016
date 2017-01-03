#include "Stairs.h"
#include <stdio.h>

Stairs::Stairs(int type, int X, int Y, int item) : CObject(type, X, Y, STAIR_WIDTH, STAIR_HEIGHT, item)
{
	isMovement = false;
}

void Stairs::Update(int DeltaTime)
{

}

void Stairs::Render()
{

}
void Stairs::Draw()
{
	/*brick.draw();*/
}
Stairs::Stairs() :CObject()
{

}
Stairs::~Stairs()
{

}

