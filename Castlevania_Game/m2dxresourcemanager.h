#pragma once

#include "m2dxutil.h"
#include "m2dxd3dx.h"
#include "m2dxdsound.h"

typedef map<string, M2DXTexture*> M2DXTextureMap;
typedef pair<string, M2DXTexture*> M2DXTexturePair;

typedef map<string, CSound*> M2DXSoundMap;
typedef pair<string, CSound*> M2DXSoundPair;

class M2DXResourceManager
{
public:
	static M2DXResourceManager* getInstance();

	M2DXResourceManager();
	~M2DXResourceManager();

	bool init();

	void addTextureWithFile(LPCTSTR fileName);
	M2DXTexture* getTextureByName(LPCTSTR textureName);

	void addSoundWithFile(LPCTSTR fileName);
	CSound* getSoundByName(LPCTSTR soundName);

private:
	static M2DXResourceManager* instance;

	void release();

	M2DXTextureMap textureMap;
	M2DXSoundMap soundMap;
};
