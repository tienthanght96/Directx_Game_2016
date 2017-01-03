#pragma once

#define DOOR_DEFAULT_ANIMATE_RATE 2
#define DOOR_CLOSE_RATE 5
#define DOOR_BEGIN_RATE 100

#define DOOR_CHANGE_STATE_TIME 500

#define DOOR_FRAME_BEGIN "DoorBegin"
#define DOOR_FRAME_END_0 "DoorEnd0"
#define DOOR_FRAME_END_1 "DoorEnd1"
#define DOOR_FRAME_MIDLE "DoorMidle"
#define DOOR_NORMAL "DoorNomal"

#include "SweptAABB.h"
#include "CObject.h"
#include "m2dxbasesprite.h"
#include "SmallHeart.h"
#include "SimonBelmont.h"
#include "Camera.h"
#include "Stage.h"

#define DOOR_WIDTH 16
#define DOOR_HEIGHT 96
#define DOOR_SPRITE "Resources\\Sprites\\Door\\Door.png"
#define DOOR_SHEET "Resources\\Sprites\\Door\\Door"


class Door : public CObject, M2DXAnimatedSprite
{
	enum DoorState
	{
		Begin,
		Open,
		Midle,
		Close,
		End
	};
public:
	Door(int X, int Y, int item);
	SweptAABB *swept = new SweptAABB();
	void Update(int DeltaTime);
	bool updateCollis(CObject* Ob);
	void updateCamera(SimonBelmont* simon);
	void Draw();
	inline DoorState getState() { return state; };
	inline void setState(DoorState nextState) { state = nextState; };
	Door() {};
	~Door() {};
protected:
	int getAnimateRate() override ;
	string getNextFrame() override;
private:
	int defaultX;
	int defaultY;
	DoorState state;
	void updateInfo();
	void updatePosition();
	int remainingChangeStateTime;
	void updateState(int deltaTime);
};

