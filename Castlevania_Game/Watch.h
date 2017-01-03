#pragma once

#include "Stage.h"
#include "CObject.h"
#include "Box.h"
#include "SweptAABB.h"

class Watch : public CObject
{
public:
	Watch();
	~Watch();

	void Update(int deltaTime, CObject* simon);

	void Draw() override {};
private:
	int remainingPauseGame;
};