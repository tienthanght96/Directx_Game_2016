#include "ResourceManager.h"
#include <string.h>
ResourceManager* ResourceManager::instance = NULL;
ResourceManager::ResourceManager()
{
	listTexture.push_back(new Texture(8, 3, 4));
	listTexture.at(listTexture.size() - 1)->Load("image/simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//background image
	for (int i = MIN_BG_ID; i <= MAX_BG_ID; i++)
	{
		char* fileName = new char[11];
		sprintf_s(fileName, 12, "tile\\%d.png", i);

		listTexture.push_back(new Texture(1, 1, 1));
		listTexture.at(listTexture.size() - 1)->Load(fileName);
	}
}

ResourceManager::~ResourceManager(void)
{
	if (!listTexture.empty())
		listTexture.clear();
}

void ResourceManager::Release()
{
	if (!listTexture.empty())
		listTexture.clear();
}

Texture* ResourceManager::GetTexture(char* fileName)
{
	int size = listTexture.size();
	Texture * texture;
	for (int i = 0; i < size; ++i)
	{
		texture = listTexture[i];
		if (strcmp(texture->FileName, fileName) == 0)
			return texture;
	}
	char text[100];
	sprintf_s(text, 101, "[ResourceManager.cpp] Cannot get Texture[%s]", fileName);
	GLMessage(text);
	return NULL;
}

ResourceManager* ResourceManager::GetInstance()
{
	if (instance == NULL) {
		instance = new ResourceManager();
	}
	return instance;
}