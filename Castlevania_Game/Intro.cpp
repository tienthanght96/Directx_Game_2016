#include "Intro.h"

void Intro::Init()
{
	screen.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Intro\\Intro"));
	screen.setFlipX(false);
	screen.setPosition(M2DXPoint(0,10));
	simonIntro = new SimonBelmont(256, 178);
	simonIntro->setFlipX(true);
	simonIntro->autoWalking = true;
	simonIntro->setactionState(SimonBelmont::ActionState::Walking);
	simonIntro->setLockLeft(0);
	simonIntro->setLockRight(560);
	cloud.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Intro\\Cloud"));
	cloud.setFlipX(false);
	cloud.setPosition(M2DXPoint(226,67));
	bat1 = new BlackBat(34,116, 0.005, -0.0015);
	bat2 = new BlackBat(138, 100, -0.007, -0.0018);
}

void Intro::update(int deltaTime)
{
	updateSimon(deltaTime);

	cloud.setPosition(M2DXPoint(cloud.getPositionX() - 0.15, cloud.getPositionY()));

	bat1->Update(deltaTime);

	bat2->Update(deltaTime);
}

void Intro::render()
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
	simonIntro->draw();
	cloud.draw();
	bat1->draw();
	bat2->draw();
	d3dxSpriteInterface->SetTransform(&oldTransformMatrix);
	d3dxSpriteInterface->End();
}

void Intro::changeScene(int deltaTime)
{
	remainingChangeScene -= deltaTime;
	if (remainingChangeScene <= 0)
		SceneManager::getInstance()->ReplaceBy(new Map(1));
}

void Intro::updateSimon(int deltaTime)
{
	if (simonIntro->getPositionX() > 120)
	{
		simonIntro->autoWalking = true;
		simonIntro->setactionState(SimonBelmont::ActionState::Walking);
		simonIntro->autoRun();
		M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
	}
	else
	{
		simonIntro->autoWalking = false;
		simonIntro->setactionState(SimonBelmont::ActionState::EnteringCastle);
		M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\falling"));
		changeScene(deltaTime);
	}
	simonIntro->update(deltaTime);
}
