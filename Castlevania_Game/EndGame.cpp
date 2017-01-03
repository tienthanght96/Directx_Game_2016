#include "EndGame.h"

void EndGame::Init()
{
	screen.setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\EndGame"));
	screen.setFlipX(false);
	screen.setPosition(M2DXPoint(0,0));
	castle.setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\Castle1"));
	castle.setFlipX(false);
	castle.setPosition(M2DXPoint(174, 40));
	castle.setRect = true;
	castle.rect.left = 0;
	castle.rect.top = 0;
	castle.rect.right = castle.getSize().width;
	castle.rect.bottom = castle.getSize().height;
	castlePoint = M2DXPoint(174,40);
	initProduce();
	isVisible = false;
	colorA = 0;
	remainingChangeSlide = 0;
	remainingDestroy = 200;
	remainingBegin = 2000;
}

void EndGame::update(int deltaTime)
{
	M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Title_Theme"));
	if (remainingBegin > 0)
		remainingBegin -= deltaTime;
	else
	{
		updateCastle(deltaTime);
	}
}

void EndGame::render()
{
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
	castle.draw();
	drawProduce();
	d3dxSpriteInterface->SetTransform(&oldTransformMatrix);
	d3dxSpriteInterface->End();
}

void EndGame::processInput(BYTE keyState[])
{
}

void EndGame::release()
{
}

void EndGame::updateProduce(int deltaTime)
{
	if (!produce.empty())
	{
		if (remainingChangeSlide > 0)
			remainingChangeSlide -= deltaTime;
		else
		{
			if (!isVisible)
			{
				colorA += 2;
				if (colorA >= 255)
				{
					colorA = 255;
					isVisible = true;
					remainingChangeSlide = TIME_CHANGE_SLIDE;
				}
			}
			else
			{
				colorA -= 2;
				if (colorA < 0)
				{
					colorA = 0;
					isVisible = false;
					vector<M2DXBaseSprite*>::iterator i = produce.begin();
					i = produce.erase(i);
					remainingChangeSlide = TIME_CHANGE_SLIDE;
				}
			}
		}
	}
}

void EndGame::initProduce()
{
	for (int i = 0;i < 5;i++)
	{
		produce.push_back(new M2DXBaseSprite());
		produce[i]->setPosition(M2DXPoint(0,50));
	}
	produce[0]->setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\DangMinhTuan"));
	produce[1]->setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\TranTienThang"));
	produce[2]->setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\TruongVinhTien"));
	produce[3]->setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\GVHD"));
	produce[4]->setTexture(M2DXResourceManager::getInstance()->getTextureByName("EndGame\\End"));
}

void EndGame::drawProduce()
{
	if (!produce.empty())
	{
		vector<M2DXBaseSprite*>::iterator i = produce.begin();
		(*i)->draw(D3DCOLOR_ARGB(colorA,255,255,255));
	}
}

void EndGame::updateCastle(int deltaTime)
{
	if (castle.rect.bottom > 0)
	{
		if (remainingDestroy > 0)
			remainingDestroy -= deltaTime;
		else
		{
			if (castlePoint.x == 174 || castlePoint.x == 173)
				castlePoint.x = 175;
			else
				castlePoint.x = 173;
			castlePoint.y += 0.2f;
			castle.setPosition(castlePoint);
			castle.setRect = true;
			castle.rect.left = 0;
			castle.rect.top = 0;
			castle.rect.right = castle.getSize().width;
			castle.rect.bottom = castle.getSize().height - (castlePoint.y - 40);
			remainingDestroy = TIME_DESTROY;
		}
	}
	else
		updateProduce(deltaTime);
}

