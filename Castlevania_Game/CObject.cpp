#include "CObject.h"

CObject::CObject(int type, int x, int y, int width, int height, int item) 
{
	_type = type;
	_x = x * 2;
	_y = y * 2;
	_width = width  ;
	_height = height ;
	_bound.left = _x;
	_bound.top = _y;
	_bound.right = _x + _width;
	_bound.bottom = _y + _height;
	_box.x = _x;
	_box.y = _y;
	_box.w = _width;
	_box.h = _height;
	_item = item;
	pointX = x;
	pointY = y;
	isDead = false;
}

void CObject::UpdatePosition(int time)
{
	_vy += _gravity * time;
	_x += int(_vx * time);
	_y += int(_vy * time);
}



CObject::~CObject()
{

}
CObject::CObject()
{

}