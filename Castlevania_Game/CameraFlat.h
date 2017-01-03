#ifndef _CAMERAFLAT_H_
#define _CAMERAFLAT_H_
using namespace std;
class CameraFlat
{
public:
	int _x;
	int _y;
	int _width;
	int _height;
	CameraFlat();
	CameraFlat(int x, int y, int width, int height);
	~CameraFlat();
};

#endif