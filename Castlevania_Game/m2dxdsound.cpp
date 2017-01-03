// Copied and edited from many sources.
// Please do not care about this shit.

#include "m2dxdsound.h"

M2DXDSound* M2DXDSound::instance = nullptr;

CSoundManager* M2DXDSound::soundManager = nullptr;

M2DXDSound* M2DXDSound::getInstance()
{
	if (!instance)
	{
		instance = new M2DXDSound();
	}

	return instance;
}

M2DXDSound::M2DXDSound() 
{}

M2DXDSound::~M2DXDSound()
{
	release();
}

void M2DXDSound::release()
{
	if (soundManager)
	{
		delete soundManager;
		soundManager = nullptr;
	}

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool M2DXDSound::init(HWND hWnd)
{
	soundManager = new CSoundManager();

	auto result = soundManager->Initialize(hWnd, DSSCL_PRIORITY);
	if (result)
	{
		return false;
	}

	result = soundManager->SetPrimaryBufferFormat(2, 22050, 16);
	if (result)
	{
		return false;
	}

	return true;
}

CSound* M2DXDSound::createSoundWithFile(LPCSTR fileName)
{
	CSound* sound;

	auto result = soundManager->Create(&sound, (LPTSTR)fileName);

	return sound;
}

void M2DXDSound::play(CSound* sound)
{
	sound->Play();
}

void M2DXDSound::loop(CSound* sound)
{
	sound->Play(0 , 0,  DSBPLAY_LOOPING);
}

void M2DXDSound::stop(CSound* sound)
{
	sound->Stop();
}

void M2DXDSound::play(CSound * sound, LONG volume, LONG Frequency)
{
	sound->Play(volume,Frequency);
}
