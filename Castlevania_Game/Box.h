#pragma once
class Box
{
public:
	Box();
	Box(float _x, float _y, float _w, float _h, float _vx, float _vy);
	Box(float _x, float _y, float _w, float _h);
	// position of top-left corner
	float x, y;

	// dimensions
	float w, h;

	// velocity
	float vx, vy;
	~Box();
};

