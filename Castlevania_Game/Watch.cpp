#include "Watch.h"

Watch::Watch()
{
	remainingPauseGame = 2000;
	M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\splashwater"));

}

Watch::~Watch()
{
}

void Watch::Update(int deltaTime, CObject * simon)
{
	if (remainingPauseGame > 0)
	{
		remainingPauseGame -= deltaTime;
		Stage::getInstance()->pauseGame = true;
	}
	else
	{
		Stage::getInstance()->pauseGame = false;
		isDead = true;
	}
}
