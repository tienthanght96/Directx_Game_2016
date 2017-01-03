#pragma once

#include "Camera.h"
#include "Number.h"
#include "ResourceManager.h"
#include "Score.h"
#include "Time.h"
#include "Stage.h"
#include "Heart.h"
#include "BloodSimon.h"
#include "BloodManager.h"
#include "Wepon.h"
#include "GetWepon.h"

class ScoreManager : public M2DXBaseSprite
{
private:
	M2DXBaseSprite* scoreText;
	M2DXBaseSprite heartImage;
	M2DXBaseSprite rect;
	M2DXBaseSprite P;
	Wepon* wepon;
	vector<BloodSimon*> simon;
	vector<BloodSimon*> bloodenemy;
	vector<Number*> Pre;
	vector<Number*> score;
	M2DXBaseSprite* player;
	M2DXBaseSprite* enemy;
	M2DXBaseSprite* timeText;
	vector<Number*> time;
	vector<Number*> stage;
	M2DXBaseSprite* stageText;
	vector<Number*> heart;
	M2DXBaseSprite* life;
	static ScoreManager* _instance;
	void initBlood();
	void updateWepon(M2DXPoint location);
	void updateBloodSimon(M2DXPoint location);
	void updateBloodEnemy(M2DXPoint location);
	void drawBlood();
	void drawText(M2DXBaseSprite* sprite, M2DXPoint location, string s);
	void drawNumber(vector<Number*> list);
	void initNumber(vector<Number*> &list, int number);
	void updateNumber(vector<Number*> &list, int data, M2DXPoint location);
	void initText(string temp, M2DXBaseSprite* &sprite);
public:	
	ScoreManager() {};
	~ScoreManager() {};
	static ScoreManager* getInstance();
	void InitializeState();
	void Update();
	void Render();
	void Pause() {};
	void Resume() {};
	void Release() {};
	
};