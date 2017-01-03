#pragma once

#include "Texture.h"
#include "m2dx.h"
#include "Global.h"
#include "ResourceManager.h"
#include "Camera.h"

typedef pair<int, string> NamePair;
typedef pair<int, M2DXBaseSprite **> MaptPair;
typedef pair<int, M2DXTexture*> TexturePair;
typedef pair<int, D3DXVECTOR2> SizePair;
typedef pair<int, int> NumberPair;

class BackgroundLoader : public M2DXBaseSprite
{
public:
	static BackgroundLoader* _instance;
	static BackgroundLoader* getInstance();
	bool setColor = false;
	BackgroundLoader();
	BackgroundLoader(int mapW, int mapH, Camera *);
	~BackgroundLoader(void);
	//Kích thước của map theo Tile (8px*8px)
	int row = 0;
	int col = 0;
	int mapWidth;
	int mapHeight;
	Camera *camera;
	int **boardTile; //lưu id của tile là background
	M2DXBaseSprite **boardTexture;
	void LoadResource();
	//Load resources background 
	void UpdateRender(int time,int deltaTime);
private:
	int remainingChangeColor = 1;
	int remainingEnd = 500;
	int colorR, colorG, colorB;
	void updateColor(int deltaTime);
	std::map<int, string> mapName;
	std::map<int, M2DXTexture*> mapTexture;
	std::map<int, M2DXBaseSprite **> mapManager;
	std::map<int, D3DXVECTOR2> mapSize;
};