#include "Camera.h"
#include "Stage.h"

Camera* Camera::Instance = 0;

Camera* Camera::getInstance()
{
	if (Instance == 0)
	{
		Instance = new Camera();
	}
	return Instance;
}

Camera::Camera()
{
	this->deltaScaleX = 1;
	this->deltaScaleY = 1;
	this->deltaAngle = 3.14 / 15;
	this->width = DEFAULT_WINDOW_WIDTH;
	this->height = DEFAULT_WINDOW_HEIGHT;
	this->angle = 0;
	this->scaleFactors = DirectX::XMFLOAT3(1.0f,1.0f,1.0f);
	following = nullptr;
	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{

}

void Camera::Update()
{
		M2DXPoint position = this->following->getPosition();
		if (!(BossX == cameraX && BossY == cameraY))
		if (this->following && this->IsFollowing())
		{
			updateFlat();			
			if (changeState == false)
			if (setCam == false)
			{
				if (position.x*2 <= (listFlat[flat]->_x * 2 + DEFAULT_WINDOW_WIDTH / 2 ))
					cameraX = listFlat[flat]->_x * 2 + this->width / 2;
				else
					if (position.x * 2 >= (listFlat[flat]->_x * 2 + listFlat[flat]->_width * 2) - width / 2)
						cameraX = (listFlat[flat]->_x * 2 + listFlat[flat]->_width * 2) - width / 2;
					else
						cameraX = position.x * 2;
			}
			cameraY = listFlat[flat]->_y*2 + listFlat[flat]->_height;

			setCam = false;
		}

		this->viewMatrix = D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-cameraX , - cameraY , 0, 1);
}

void Camera::SetTransform(LPDIRECT3DDEVICE9 d3ddv) const
{
	d3ddv->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	d3ddv->SetTransform(D3DTS_WORLD, &identityMatrix);
	d3ddv->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::Follow(SimonBelmont* following)
{
	this->following = following;
}

void Camera::Unfollow()
{
	this->following = nullptr;
}

void Camera::updateFlat()
{
	if ((following->getPositionY() + following->getSize().height) >= (listFlat[flat]->_y + listFlat[flat]->_height) && following->getActionState() == SimonBelmont::ActionState::StairWalking && following->getStairDirection() == SimonBelmont::StairDirection::Down )
	{
		setFlat(flat + 1);
		if (following->getFlipX() == true)
			following->setPositionX(following->getPositionX() + 16);
		else
			following->setPositionX(following->getPositionX() - 16);
		following->setPositionY(following->getPositionY() + 64);
	}
	if (following->getPositionY()  <= (listFlat[flat]->_y + 64) && following->getActionState() == SimonBelmont::ActionState::StairWalking && following->getStairDirection() == SimonBelmont::StairDirection::Up)
	{
		setFlat(flat - 1);
		if(following->getFlipX() == true)
		following->setPositionX(following->getPositionX() + 16);
		else
			following->setPositionX(following->getPositionX() - 16);
		following->setPositionY(following->getPositionY() - 64);
	}
}

bool Camera::IsFollowing() const
{
	return this->following != nullptr;
}

void Camera::Scale()
{
	if ((deltaScaleX < 0 || deltaScaleY < 0) && (scaleFactors.x <= 1 || scaleFactors.y <= 1))
	{
		scaleFactors.x = 1;
		scaleFactors.y = 1;
	}
	else
	{
		scaleFactors.x += deltaScaleX;
		scaleFactors.y += deltaScaleY;
	}
}

RECT Camera::getBound()
{
	RECT tempRect = RECT();

	tempRect.top = (long)(cameraY - height / 2);
	tempRect.left = (long)(cameraX - width / 2);
	tempRect.right = (long)(tempRect.left + width);
	tempRect.bottom = (long)(tempRect.top + height);

	return tempRect;
}


