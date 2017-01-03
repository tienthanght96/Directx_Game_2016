#pragma once

#include "m2dxbasesprite.h"
#include "m2dxanimatedsprite.h"

#define BLOOD_SIMON_SPRITE "Font\\Blood\\BloodSimonSheet.png"
#define BLOOD_SIMON_SHEET "Font\\Blood\\BloodSimonSheet"
#define BLOOD_ENEMY_SPRITE "Font\\Blood\\BloodEnemySheet.png"
#define BLOOD_ENEMY_SHEET "Font\\Blood\\BloodEnemySheet"


class BloodSimon : public M2DXAnimatedSprite
{
public:
	string state;
	void setBloodState(string bloodState) { state = bloodState; };
	void Update(M2DXPoint location);
	void Draw();
	BloodSimon(string nameObject);
	~BloodSimon() {};
protected:
	int getAnimateRate() override { return 0; };
	string getNextFrame() override;
	void updateFrame();
private:
	void updatePosition(M2DXPoint location);
};

