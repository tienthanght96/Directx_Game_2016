#include "Map.h"
#include "Stage.h"

void Map::Init()
{
	map.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Map\\FullMap"));
	map.setFlipX(false);
	map.setPosition(M2DXPoint(256,10));
	simonFromMap.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Map\\SimonFromMap"));
	simonFromMap.setFlipX(false);
	if (_level == 1)
	{
		simonFromMap.setPosition(M2DXPoint(154, 112));
		boss = new BossFromMap(91, 80);
	}
	if (_level == 2)
	{
		simonFromMap.setPosition(M2DXPoint(82, 84));
		boss = new BossFromMap(172,66);
	}
	simonIntro = new SimonBelmont(2, 175);
	simonIntro->setFlipX(false);
	simonIntro->autoWalking = true;
	simonIntro->setactionState(SimonBelmont::ActionState::Walking);
	simonIntro->setLockLeft(0);
	simonIntro->setLockRight(560);
}

void Map::update(int deltaTime)
{
	if (map.getPositionX() > 0)
		map.setPositionX(map.getPositionX() - 3);
	else
	{
		updateFrame(deltaTime);
		boss->Update(deltaTime);
		updateSimon(deltaTime);
	}
}

void Map::render()
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
	map.draw();
	if (map.getPositionX() <= 0)
	{
		simonFromMap.draw();
		boss->draw();
		simonIntro->draw();
	}
	d3dxSpriteInterface->SetTransform(&oldTransformMatrix);
	d3dxSpriteInterface->End();
}

void Map::updateSimon(int deltaTime)
{
	if (simonIntro->getPositionX() + simonIntro->getSize().width <= 256)
	{
		simonIntro->autoWalking = true;
		simonIntro->setactionState(SimonBelmont::ActionState::Walking);
		simonIntro->autoRun();
		M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
		simonIntro->update(deltaTime);
	}
	else
	{
		Stage::getInstance()->stage += 1;
		M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
		SceneManager::getInstance()->ReplaceBy(new Castlevania(Stage::getInstance()->nextLevel));
	}
}

void Map::updateFrame(int deltaTime)
{
	remainingChangeFrame -= deltaTime;
	if (remainingChangeFrame <= 0)
	{
		if (frame1 == true)
		{
			simonFromMap.setTexture(M2DXResourceManager::getInstance()->getTextureByName(""));
			frame1 = false;
		}
		else
		{
			simonFromMap.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Map\\SimonFromMap"));
			frame1 = true;
		}
		remainingChangeFrame = 200;
	}
}
