#pragma once

// Copied and edited from many sources.
// Please do not care about this shit.

#include "dsutil.h"

class M2DXDSound
{
public:
	static M2DXDSound* getInstance();

	~M2DXDSound();

	bool init(HWND hWnd);

	CSound* createSoundWithFile(LPCSTR fileName);

	void play(CSound* sound);
	void loop(CSound* sound);
	void stop(CSound* sound);
	void play(CSound* sound, LONG volume, LONG frequency);

private:
	static M2DXDSound* instance;
	static CSoundManager* soundManager;

	M2DXDSound();

	void release();
};
