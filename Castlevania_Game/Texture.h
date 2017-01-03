#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "m2dx.h"
#include <d3d9.h>
#include <d3dx9.h>

#include "Global.h"

class Texture {
public:
	char* FileName;
	RECT Size;
	LPDIRECT3DTEXTURE9 _Texture;

	int Cols;
	int Rows;

	int Count;

	int Width;
	int Height;
	Texture() {
		FileName = NULL;
		Cols = 1;
		Rows = 1;
		Count = 1;
	};
	Texture(int cols, int rows, int count);
	~Texture();
	void Load(char* filename, D3DCOLOR transcolor = 0);
	void Render(int x, int y, float depth);
};
#endif // !_TEXTURE_H_
