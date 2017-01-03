#include "PauseScene.h"
#include "Stage.h"
#include "TileScreen.h"
#include "Castlevania.h"
#include "Score.h"
#include "Heart.h"

void PauseScene::Init()
{
	currentButton = 1;
	isEnter = false;
	colorAlpha = 0;
	colorAlphaResume = 0;
	colorAlphaText = 0;
	colorAlphaExit = 0;
	remainingUpdateScreen = TIME_UPDATE_SCREEN;
	screen.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Pause\\Resume"));
	screen.setFlipX(false);
	screen.setPosition(M2DXPoint(0,0));
	btnResune.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Pause\\btnResume"));
	btnResune.setFlipX(false);
	btnResune.setPosition(M2DXPoint(83,59));
	gameOver.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Pause\\GameOver"));
	gameOver.setFlipX(false);
	gameOver.setPosition(M2DXPoint(40, 23));
	btnRestart.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Pause\\btnRestart"));
	btnRestart.setFlipX(false);
	btnRestart.setPosition(M2DXPoint(83, 111));
	btnExit.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Pause\\btnExit"));
	btnExit.setFlipX(false);
	btnExit.setPosition(M2DXPoint(83, 163));
}

void PauseScene::update(int deltaTime)
{
	M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\GameOver"));
	updateScreen(deltaTime);
}

void PauseScene::render()
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
	screen.draw(D3DCOLOR_ARGB(colorAlpha,255,255,255));
	gameOver.draw(D3DCOLOR_ARGB(colorAlphaText, 255, 255, 255));
	drawButton();
	d3dxSpriteInterface->SetTransform(&oldTransformMatrix);
	d3dxSpriteInterface->End();
}

void PauseScene::processInput(BYTE keyState[])
{
}

void PauseScene::onKeyDown(int keyCode)
{
	if (colorAlphaExit == 255 && !isEnter)
	{
		switch (keyCode)
		{
		case DIK_UPARROW:
		{
			currentButton -= 1;
			if (currentButton <= 0)
				currentButton = 3;
		}
		break;
		case DIK_DOWNARROW:
		{
			currentButton += 1;
			if (currentButton >= 4)
				currentButton = 1;
		}
		break;
		case DIK_SPACE:
			isEnter = true;
			break;
		}
	}
}

void PauseScene::release()
{
}

void PauseScene::updateColor()
{

}

void PauseScene::updateScreen(int deltatime)
{
	if (colorAlpha < 255)
		colorAlpha += 5;
	else
		updateText();
}

void PauseScene::updateResume()
{
	if (isEnter == false)
	{
		if (btnResune.getPositionY() < 84)
		{
			btnResune.setPositionY(btnResune.getPositionY() + 0.5f);
			colorAlphaResume += 5;
		}
		else
		{
			colorAlphaResume = 255;
			updateRestart();
		}
	}
	else
		if (isEnter && currentButton == 1)
		{
			if (colorAlphaResume > 0)
			{
				btnResune.setPositionX(btnResune.getPositionX() + 0.5f);
				colorAlphaResume -= 5;
			}
			else
			{
				M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\GameOver"));
				SceneManager::getInstance()->ReplaceBy(new Castlevania(Stage::getInstance()->nextLevel));
				Stage::getInstance()->life = 3;
				Heart::getInstance()->heart = 0;
				Score::getInstance()->score = 0;
				BloodManager::getInstance()->bloodEnemy = 16;
				BloodManager::getInstance()->bloodSimon = 16;
			}
		}
		else
			if (currentButton != 1)
			{
				updateRestart();
			}
}

void PauseScene::updateRestart()
{
	if (isEnter == false)
	{
		if (btnRestart.getPositionY() < 136)
		{
			btnRestart.setPositionY(btnRestart.getPositionY() + 0.5f);
			colorAlphaRestart += 5;
		}
		else
		{
			colorAlphaRestart = 255;
			updateExit();
		}
	}
	else
		if (isEnter && currentButton == 2)
		{
			if (colorAlphaRestart > 0)
			{
				btnRestart.setPositionX(btnRestart.getPositionX() + 0.5f);
				colorAlphaRestart -= 5;
			}
			else
			{
				M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\GameOver"));
				SceneManager::getInstance()->ReplaceBy(new TileScreen());
				Stage::getInstance()->nextLevel = 1;
				Stage::getInstance()->stage = 0;
				Stage::getInstance()->life = 3;
				Heart::getInstance()->heart = 0;
				Score::getInstance()->score = 0;
				BloodManager::getInstance()->bloodEnemy = 16;
				BloodManager::getInstance()->bloodSimon = 16;
			}
		}
		else
			if (currentButton != 2)
				updateExit();
}

void PauseScene::updateExit()
{
	if (!isEnter)
	{
		if (btnExit.getPositionY() < 188)
		{
			btnExit.setPositionY(btnExit.getPositionY() + 0.5f);
			colorAlphaExit += 5;
		}
		else
			colorAlphaExit = 255;
	}
	else
		if (isEnter && currentButton == 3)
		{
			if (colorAlphaExit > 0)
			{
				btnExit.setPositionX(btnExit.getPositionX() + 0.5f);
				colorAlphaExit -= 5;
			}
			else
			{
				M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\GameOver"));
				PostMessage(M2DXWindow::getInstance()->getWindow(), WM_QUIT, 0, 0);
			}
		}
}

void PauseScene::updateText()
{
	if (gameOver.getPositionY() < 45)
	{
		gameOver.setPositionY(gameOver.getPositionY() + 0.5f);
		colorAlphaText += 5.79f;
	}
	else
	{
		colorAlphaText = 255;
		updateResume();
	}
}

void PauseScene::drawButton()
{
	if (colorAlphaExit == 255)
	{
		switch (currentButton)
		{
		case 1:
			btnResune.draw(D3DCOLOR_ARGB(colorAlphaResume, 238, 124,107));
			btnRestart.draw(D3DCOLOR_ARGB(colorAlphaRestart, 255, 255, 255));
			btnExit.draw(D3DCOLOR_ARGB(colorAlphaExit, 255, 255, 255));
			break;
		case 2:
			btnResune.draw(D3DCOLOR_ARGB(colorAlphaResume, 255, 255, 255));
			btnRestart.draw(D3DCOLOR_ARGB(colorAlphaRestart, 238, 124, 107));
			btnExit.draw(D3DCOLOR_ARGB(colorAlphaExit, 255, 255, 255));
			break;
		case 3:
			btnResune.draw(D3DCOLOR_ARGB(colorAlphaResume, 255, 255, 255));
			btnRestart.draw(D3DCOLOR_ARGB(colorAlphaRestart, 255, 255, 255));
			btnExit.draw(D3DCOLOR_ARGB(colorAlphaExit, 238, 124, 107));
			break;
		}
	}
	else
	{
		btnResune.draw(D3DCOLOR_ARGB(colorAlphaResume, 255, 255, 255));
		btnRestart.draw(D3DCOLOR_ARGB(colorAlphaRestart, 255, 255, 255));
		btnExit.draw(D3DCOLOR_ARGB(colorAlphaExit, 255, 255, 255));
	}
}
