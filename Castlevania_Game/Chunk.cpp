#include "Chunk.h"

Chunk::Chunk(int X, int Y, float velX, float velY)
{
	initWithTexture("Resources\\Sprites\\ChunkFromBrokenBlock");
	setPosition(M2DXPoint(X,Y));
	velocity.x = velX;
	velocity.y = velY;
	gravity = GRAVITY;
	if (velX < 0)
		setFlipX(true);
	else
		setFlipX(false);
}

void Chunk::Update(int DeltaTime)
{
	updatePosition(DeltaTime);
}

void Chunk::Draw()
{
	M2DXBaseSprite::draw();
}

void Chunk::updatePosition(int deltaTime)
{
	velocity.y += gravity*deltaTime;
	auto position = getPosition();
	position += velocity*deltaTime;
	setPosition(position);
}
