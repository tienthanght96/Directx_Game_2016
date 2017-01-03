#pragma once
#include <DirectXMath.h>
#include "CameraFlat.h"
#include "m2dxbasesprite.h"
#include "SimonBelmont.h"
#include "m2dxbasegamelayer.h"
#include "Global.h"
#include "CObject.h"
#include <vector>
class Camera 
{
public:
	//Constructors and Destructor
	Camera();
	~Camera();
	int flat;
	vector<CameraFlat*> listFlat;
	static Camera* getInstance();
	float cameraX, cameraY;
	//Game Functions
	SimonBelmont *following;
	void Follow(SimonBelmont *kitty);
	void Unfollow();
	void updateFlat();
	bool Camera::IsFollowing() const;
	void Rotate() { this->angle += deltaAngle; };
	void Scale();
	void Update();
	void setCamX(int positionX) { cameraX = positionX; };
	bool setCam = false;
	void SetTransform(LPDIRECT3DDEVICE9 d3ddv) const;
	RECT getBound();
	void setFlat(int m_flat) { flat = m_flat; };
public:
	bool changeState = false;
	float BossX = 0;
	float BossY = 0;
	float deltaScaleX;
	float deltaScaleY;
	float deltaAngle;
	float angle;
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;
	int width;
	int height;
private:
	static Camera*	Instance;
};

