#pragma once
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "Texture.h"
#include <vector>
using namespace std;

class ResourceManager
{
private:
	//load all resources
	//unique instance
	static ResourceManager* instance;
	//List of textures
	vector<Texture*> listTexture;
public:
	ResourceManager();
	~ResourceManager(void);
	void Release();
	//get texture
	Texture* GetTexture(char* fileName);
	//get the unique instance
	static ResourceManager* GetInstance();
};
#endif // !_RESOURCEMANAGER_H_
