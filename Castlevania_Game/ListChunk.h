#ifndef __LIST_CHUNK_H__
#define __LIST_CHUNK_H__

#include "Chunk.h"
#include <list>
using namespace std;

#define CHUNK_X 0.0625F
#define CHUNK_Y 0.1825F

class ListChunk
{
private:
public:
	ListChunk(int X, int Y);
	list<Chunk*>			m_ListChunk;
	void Update(int deltaTime);
	void Render();
	void Release();
	ListChunk() {};
	~ListChunk() {};
};

#endif