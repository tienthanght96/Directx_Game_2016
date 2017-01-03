#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "vector"
#include <list>
#include <map>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define M2_SAFE_DELETE(p) { if (p) { delete (p); (p) = nullptr; } }

using namespace std;

string getFileNameWithoutExtension(LPCSTR fileName);

struct M2DXPoint
{
	float x;
	float y;

	M2DXPoint() : x(0), y(0) { }
	M2DXPoint(float x, float y) : x(x), y(y) { }

	inline bool operator==(const M2DXPoint& point) { return x == point.x && y == point.y; }
	inline bool operator!=(const M2DXPoint& point) { return x != point.x || y != point.y; }
	inline M2DXPoint& operator+=(const D3DXVECTOR2& rhs) { x += rhs.x; y += rhs.y; return *this; }
};

struct M2DXSize
{
	float width;
	float height;

	M2DXSize() : width(0), height(0) { }
	M2DXSize(float width, float height) : width(width), height(height) { }
};

struct M2DXRectangle
{
	float left;
	float top;
	float right;
	float bottom;

	M2DXRectangle() : left(0), top(0), right(0), bottom(0) { }
	M2DXRectangle(float x, float y, float width, float height) : left(x), top(y), right(left + width), bottom(top + height) { }
	M2DXRectangle(M2DXPoint position, M2DXSize size) : left(position.x), top(position.y), right(left + size.width), bottom(top + size.height) { }

	inline bool intersectWith(M2DXRectangle rectangle) { return left <= rectangle.right && right >= rectangle.left && top <= rectangle.bottom && bottom >= rectangle.top; }
	inline bool contains(M2DXPoint position) { return left <= position.x && right >= position.x && top <= position.y && bottom <= position.y; }
};
