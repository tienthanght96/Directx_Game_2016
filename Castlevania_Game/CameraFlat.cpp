#include "CameraFlat.h"

CameraFlat::~CameraFlat()
{
}

CameraFlat::CameraFlat(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
};

CameraFlat::CameraFlat()
{};
