#include "TileScreen.h"
#include "PauseScene.h"

void TileScreen::Init()
{
	screen.setTexture(M2DXResourceManager::getInstance()->getTextureByName("TileScreen\\TileScreen"));
	screen.setFlipX(false);
	screen.setPosition(M2DXPoint(0,10));
	bat = new BatScreen(184,106);
	pushEnter.setTexture(M2DXResourceManager::getInstance()->getTextureByName("TileScreen\\PushEnter"));
	pushEnter.setFlipX(false);
	pushEnter.setPosition(M2DXPoint(73, 138));
}

void TileScreen::update(int deltaTime)
{
	if (!isEnter)
	bat->Update(deltaTime);
	
	if (isEnter)
	{
		updateColor();
		changeScene(deltaTime);
	}
}

void TileScreen::render()
{
	D3DXCOLOR color;
	color = D3DCOLOR_ARGB(colorAlpha, 0xff, 0xff, 0xff);
	auto d3dDeviceInterface = M2DXDirect3D::getInstance()->getD3DDeviceInterface();
	d3dDeviceInterface->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0);
	auto d3dxSpriteInterface = M2DXD3DX::getInstance()->getD3DXSpriteInterface();
	d3dxSpriteInterface->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX newTransformMatrix;
	D3DXMATRIX oldTransformMatrix;
	d3dxSpriteInterface->GetTransform(&oldTransformMatrix);
	D3DXVECTOR2 scaling = D3DXVECTOR2(SCALE_FACTOR, SCALE_FACTOR);
	D3DXMatrixTransformation2D(&newTransformMatrix, NULL, 0.0f, &scaling, NULL, 0.0f, NULL);
	newTransformMatrix *= oldTransformMatrix;
	d3dxSpriteInterface->SetTransform(&newTransformMatrix);
	screen.draw();
	bat->Draw();
	pushEnter.draw(color);
	d3dxSpriteInterface->SetTransform(&oldTransformMatrix);
	d3dxSpriteInterface->End();
}

void TileScreen::processInput(BYTE keyState[])
{
	if (isKeyDown(DIK_SPACE, keyState))
		isEnter = true;
}

void TileScreen::release()
{
}

void TileScreen::updateColor()
{
	remainingChangeColor -= 1;
	if (remainingChangeColor == 0)
	{
		if (colorAlpha == 0)
			colorAlpha = 255;
		else
			colorAlpha = 0;
		remainingChangeColor = 4;
	}
}

void TileScreen::changeScene(int deltaTime)
{
	remainingChangeScene -= deltaTime;
	if (remainingChangeScene <= 0)
		SceneManager::getInstance()->ReplaceBy(new Intro());
	
}
