#include "m2dxbasesprite.h"

M2DXBaseSprite::M2DXBaseSprite() : position(M2DXPoint(0, 0)) { }

M2DXBaseSprite::~M2DXBaseSprite()
{
	if (texture)
	{
		texture = nullptr;
	}
}

bool M2DXBaseSprite::initWithFile(LPCSTR fileName)
{
	texture = M2DXD3DX::getInstance()->createTextureWithFile(fileName);

	if (!texture)
	{
		return false;
	}

	return true;
}

bool M2DXBaseSprite::initWithTexture(LPCSTR textureName)
{
	texture = M2DXResourceManager::getInstance()->getTextureByName(textureName);

	if (!texture)
	{
		return true;
	}

	return false;
}

void M2DXBaseSprite::render()
{
	auto spriteInterface = getSpriteInterface();

	D3DXMATRIX oldTransformMatrix;
	spriteInterface->GetTransform(&oldTransformMatrix);
	if (setRect == true) flipX = false;
	if (flipX)
	{
		D3DXMATRIX newTransformMatrix;

		D3DXVECTOR2 scalingCenter = D3DXVECTOR2(position.x + getSize().width / 2, position.y + getSize().height / 2);
		D3DXVECTOR2 scaling = D3DXVECTOR2(-1, 1);
		D3DXMatrixTransformation2D(&newTransformMatrix, &scalingCenter, 0.0f, &scaling, NULL, 0.0f, NULL);
		newTransformMatrix *= oldTransformMatrix;

		getSpriteInterface()->SetTransform(&newTransformMatrix);
	}

	M2DXIDrawable::render();

	spriteInterface->SetTransform(&oldTransformMatrix);
}

void M2DXBaseSprite::render(D3DXCOLOR color)
{
	auto spriteInterface = getSpriteInterface();

	D3DXMATRIX oldTransformMatrix;
	spriteInterface->GetTransform(&oldTransformMatrix);
	if (setRect == true) flipX = false;
	if (flipX)
	{
		D3DXMATRIX newTransformMatrix;

		D3DXVECTOR2 scalingCenter = D3DXVECTOR2(position.x + getSize().width / 2, position.y + getSize().height / 2);
		D3DXVECTOR2 scaling = D3DXVECTOR2(-1, 1);
		D3DXMatrixTransformation2D(&newTransformMatrix, &scalingCenter, 0.0f, &scaling, NULL, 0.0f, NULL);
		newTransformMatrix *= oldTransformMatrix;

		getSpriteInterface()->SetTransform(&newTransformMatrix);
	}

	M2DXIDrawable::render(color);

	spriteInterface->SetTransform(&oldTransformMatrix);
}

RECT M2DXBaseSprite::getSourceRectangle()
{
	if (setRect == false)
	{
		auto size = getSize();

		RECT result;
		result.left = 0;
		result.top = 0;
		result.right = size.width;
		result.bottom = size.height;

		return result;
	}
	return rect;
}

D3DXVECTOR3 M2DXBaseSprite::getDrawingPosition()
{
	return D3DXVECTOR3((float)position.x, (float)position.y, 0.0f);
}

D3DCOLOR M2DXBaseSprite::getRenderedColor()
{
	return 0xFFFFFFFF;
}
