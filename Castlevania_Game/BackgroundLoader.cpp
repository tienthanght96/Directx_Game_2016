#include "BackgroundLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#define PI 3.14
using namespace std;
BackgroundLoader* BackgroundLoader::_instance = 0;

BackgroundLoader * BackgroundLoader::getInstance()
{
	if (!_instance)
	{
		_instance = new BackgroundLoader();
	}
	return _instance;
}
BackgroundLoader::BackgroundLoader()
{
	mapName.insert(NamePair(1, "Map\\Level1\\background.txt"));
	mapTexture.insert(TexturePair(1, M2DXResourceManager::getInstance()->getTextureByName("tile\\1")));
	mapName.insert(NamePair(2, "Map\\Level2\\background.txt"));
	mapTexture.insert(TexturePair(2, M2DXResourceManager::getInstance()->getTextureByName("tile\\2")));
}
BackgroundLoader::BackgroundLoader(int mapW, int mapH, Camera *camera)
{
	mapWidth = mapW;
	mapHeight = mapH;
	boardTile = NULL;
	this->camera = camera;
	boardTexture = NULL;

}

BackgroundLoader::~BackgroundLoader()
{
	// Sua lai
	delete[] boardTile;
	boardTile = NULL;
	delete[] boardTexture;
	boardTexture = NULL;
}


void BackgroundLoader::LoadResource()
{
	int i = 1;
	while (i <= 2)
	{
		auto stringName = mapName[i];
		auto texture = mapTexture[i];
		string line;

		ifstream myfile(stringName, ios::in | ios::out);

		if (myfile.is_open())
		{
			getline(myfile, line);
			col = atoi((line).c_str());
			G_MapWidth[i-1] = col * 16;
			getline(myfile, line);
			row = atoi(line.c_str());
			G_MapHeight[i-1] = row * 16;
			boardTile = new int*[row];
			for (int i = 0; i < row; i++)
			{
				boardTile[i] = new int[col];
			}

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					myfile >> boardTile[i][j];
				}
			}
		}
		//Texture
		boardTexture = new M2DXBaseSprite*[row];
		for (int i = 0; i < row; i++)
		{
			boardTexture[i] = new M2DXBaseSprite[col];
		}
		{
			for (int i = 0;i < row;i++)
				for (int j = 0; j < col; j++)
				{
					boardTexture[i][j].setTexture(texture);
					boardTexture[i][j].rect.top = 0;;
					boardTexture[i][j].rect.left = boardTile[i][j] * 16;
					boardTexture[i][j].rect.right = boardTexture[i][j].rect.left + 16;
					boardTexture[i][j].rect.bottom = boardTexture[i][j].rect.top + 16;
					boardTexture[i][j].setRect = true;
					boardTexture[i][j].setPosition(M2DXPoint(j * 16, i * 16));
				}
		}
		mapManager.insert(MaptPair(i,boardTexture));
		mapSize.insert(SizePair(i,D3DXVECTOR2(row,col)));
		i++;
	}
}
void BackgroundLoader::UpdateRender(int level,int deltaTime)
{
	updateColor(deltaTime);
	auto board = mapManager[level];
	auto size = mapSize[level];
	for (int i = 0;i< size.x;i++)
		for (int j = 0; j < size.y; j++)
		{
			board[i][j].draw(D3DCOLOR_ARGB(255,colorR,colorG,colorB));
		}
}

void BackgroundLoader::updateColor(int deltaTime)
{
	if (setColor == true)
	{
		if (remainingEnd > 0)
		{
			remainingEnd -= deltaTime;
			if (remainingChangeColor > 0)
			{
				remainingChangeColor -= 1;
				colorR = 0;
				colorG = 191;
				colorB = 255;
			}
			else
			{
				remainingChangeColor = 1;
				colorR = 255;
				colorG = 255;
				colorB = 255;
			}
		}
		else
		{
			remainingEnd = 500;
			setColor = false;
			remainingChangeColor = 1;
			colorR = 255;
			colorG = 255;
			colorB = 255;
		}
	}
	else
	{
		remainingEnd = 500;
		remainingChangeColor = 1;
		colorR = 255;
		colorG = 255;
		colorB = 255;
	}
}



