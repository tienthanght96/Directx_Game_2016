#pragma once

#include "CObject.h"
#include "Box.h"
#include "SweptAABB.h"

#define DAGGER_SPRITE "Resources\\Sprites\\Weapons\\Dagger\\DaggerSheet.png"
#define DAGGER_SHEET "Resources\\Sprites\\Weapons\\Dagger\\DaggerSheet"

#define DAGGER_ANIMATE_RATE 8

#define GRAVITY 0.00048828125F

#define DAGGER_X 0.1825F

#define DAGGER "Dagger"

#define DAGGER_WIDTH 32
#define DAGGER_HEIGHT 18

class Dagger : public M2DXAnimatedSprite, CObject
{
public:
	Dagger(int X, int Y, bool AD);
	~Dagger();

	void Update(int deltaTime, CObject* simon);

	void Draw() override;

protected:
	string getNextFrame() override { return DAGGER; };
	int getAnimateRate() override { return DAGGER_ANIMATE_RATE; }

private:
	D3DXVECTOR2 velocity;
	SweptAABB *swept = new SweptAABB();
	void updateInfor();
	void updatePosition(CObject* simon, int deltaTime);
};