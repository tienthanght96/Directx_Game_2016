#ifndef _CHUNK_H__
#define __CHUNK_H__

#include "m2dxbasesprite.h"

#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 32
#define CHUNK_SPRITE "Resources\\Sprites\\ChunkFromBrokenBlock.png"

#define GRAVITY 0.00048828125F


class Chunk : M2DXBaseSprite
{
public:
	Chunk(int X, int Y, float velX, float velY);
	void Update(int DeltaTime);
	void Draw();
	Chunk() {};
	~Chunk() {};
private:
	D3DXVECTOR2 velocity;
	void updatePosition(int deltaTime);
	float gravity;
};
#endif
