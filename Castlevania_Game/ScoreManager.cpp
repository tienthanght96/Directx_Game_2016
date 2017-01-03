#include "ScoreManager.h"
ScoreManager*	ScoreManager::_instance = 0;

void ScoreManager::initBlood()
{
	for (int i = 0;i < 16;i++)
	{
		simon.push_back(new BloodSimon("Simon"));
	}
	for (int i = 0;i < 16;i++)
	{
		bloodenemy.push_back(new BloodSimon("Enemy"));
	}
}

void ScoreManager::updateWepon(M2DXPoint location)
{
	switch (GetWepon::getInstance()->wepon)
	{
	case 1:
		wepon->setWeponState("Axe");
		break;
	case 2:
		wepon->setWeponState("Boomerang");
		break;
	case 3:
		wepon->setWeponState("HolyWater");
		break;
	case 4:
		wepon->setWeponState("Dagger");
		break;
	case 5:
		wepon->setWeponState("Watch");
		break;
	}
	wepon->Update(location);
}

void ScoreManager::updateBloodSimon(M2DXPoint location)
{
	int length = 0;
	if (BloodManager::getInstance()->bloodSimon >= 0)
	{
		for (int i = 0;i < BloodManager::getInstance()->bloodSimon; i++)
		{
			simon[i]->setBloodState("Full");
			simon[i]->Update(M2DXPoint(location.x + length, location.y));
			length += 4;
		}
		for (int i = BloodManager::getInstance()->bloodSimon;i < 16; i++)
		{
			simon[i]->setBloodState("Empty");
			simon[i]->Update(M2DXPoint(location.x + length, location.y));
			length += 4;
		}

	}
	else
	{
		for (int i = 0;i < 16; i++)
		{
			simon[i]->setBloodState("Empty");
			simon[i]->Update(M2DXPoint(location.x + length, location.y));
			length += 4;
		}
	}
}

void ScoreManager::updateBloodEnemy(M2DXPoint location)
{
	int length = 0;
	if (BloodManager::getInstance()->bloodEnemy >= 0)
	{
		for (int i = 0; i < BloodManager::getInstance()->bloodEnemy; i++)
		{
			bloodenemy[i]->setBloodState("Full");
			bloodenemy[i]->Update(M2DXPoint(location.x + length, location.y));
			length += 4;
		}
		for (int i = BloodManager::getInstance()->bloodEnemy; i < 16; i++)
		{
			bloodenemy[i]->setBloodState("Empty");
			bloodenemy[i]->Update(M2DXPoint(location.x + length, location.y));
			length += 4;
		}
	}
	else
	{
		for (int i = 0;i < 16; i++)
		{
			bloodenemy[i]->setBloodState("Empty");
			bloodenemy[i]->Update(M2DXPoint(location.x + length, location.y));
			length += 4;
		}
	}
}

void ScoreManager::drawBlood()
{
	for (int i = 0;i < 16;i++)
	{
		simon[i]->Draw();
	}
	for (int i = 0;i < 16;i++)
	{
		bloodenemy[i]->Draw();
	}
}

void ScoreManager::drawText(M2DXBaseSprite * sprite, M2DXPoint location,string s)
{
	int length = 0;
	int i = 0;
	int n = s.length();
	try
	{
		while (i<n)
		{
			sprite[i].setPosition(M2DXPoint(location.x + length, location.y));
			sprite[i].setFlipX(false);
			sprite[i].draw();
			length += sprite[i].getSize().width;
			i++;
		}
	}
	catch (exception ex)
	{}
}

void ScoreManager::drawNumber(vector<Number*> list)
{
	for (int i = 0;i < list.size();i++)
	{
		list[i]->Draw();
	}
}

void ScoreManager::initNumber(vector<Number*> &list, int count)
{
	int i = 0;
	while (i < count)
	{
		list.push_back(new Number());
		i++;;
	}
}

void ScoreManager::updateNumber(vector<Number*> &list, int data, M2DXPoint location)
{
	if (data < 0)
		data = 0;
	int length = 8 * (list.size() - 1);
	for (int i = list.size() - 1;i >= 0;i--)
	{
		list[i]->data = data % 10;
		list[i]->Update(M2DXPoint(location.x +  length, location.y));
		length -= 8;
		data = data / 10;
	}
}

void ScoreManager::initText( string s, M2DXBaseSprite * &sprite)
{
	
	int n = s.length();
	sprite = new M2DXBaseSprite[n];
	for (int i = 0;i < n;i++)
	{
		string temp = "Font\\";
		temp.push_back(s[i]);
		sprite[i].setTexture(M2DXResourceManager::getInstance()->getTextureByName(temp.c_str()));
	}
}


ScoreManager* ScoreManager::getInstance()
{
	if (!_instance)
	{
		_instance = new ScoreManager();
	}
	return _instance;
}

void ScoreManager::InitializeState()
{
	
	//
	wepon = new Wepon();
	heartImage.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Font\\Heart"));
	P.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Font\\P"));
	rect.setTexture(M2DXResourceManager::getInstance()->getTextureByName("Font\\Rect"));
	//
	initText( "SCORE" ,scoreText);
	initText("PLAYER", player);
	initText("ENEMY", enemy);
	initText("TIME", timeText);
	initText("STAGE", stageText);
	initNumber(score, 6);
	initNumber(time, 3);
	initNumber(stage, 2);
	initNumber(heart, 2);
	initNumber(Pre, 2);
	initBlood();
}

void ScoreManager::Update()
{
	updateNumber(score, Score::getInstance()->score, M2DXPoint(Camera::getInstance()->cameraX/2 - 75, Camera::getInstance()->cameraY/2 - 110));
	if(Time::getInstance()->time >= 0)
	updateNumber(time, Time::getInstance()->time, M2DXPoint(Camera::getInstance()->cameraX / 2 + 25, Camera::getInstance()->cameraY / 2 - 110));
	else
		updateNumber(time, 0, M2DXPoint(Camera::getInstance()->cameraX / 2 + 25, Camera::getInstance()->cameraY / 2 - 110));
	updateNumber(stage, Stage::getInstance()->stage, M2DXPoint(Camera::getInstance()->cameraX / 2 + 110, Camera::getInstance()->cameraY / 2 - 110));
	updateNumber(heart, Heart::getInstance()->heart, M2DXPoint(Camera::getInstance()->cameraX / 2 + 61, Camera::getInstance()->cameraY / 2 - 95));
	updateNumber(Pre, Stage::getInstance()->life, M2DXPoint(Camera::getInstance()->cameraX / 2 + 61, Camera::getInstance()->cameraY / 2 - 80));
	updateBloodSimon(M2DXPoint(Camera::getInstance()->cameraX / 2 - 70, Camera::getInstance()->cameraY / 2 - 93));
	updateBloodEnemy(M2DXPoint(Camera::getInstance()->cameraX / 2 - 70, Camera::getInstance()->cameraY / 2 - 78));
	updateWepon(M2DXPoint(Camera::getInstance()->cameraX / 2 + 7, Camera::getInstance()->cameraY / 2 - 88));
}

void ScoreManager::Render()
{
	drawText(scoreText,M2DXPoint(Camera::getInstance()->cameraX/2 - 125,Camera::getInstance()->cameraY/2 - 110),"SCORE");
	drawText(player, M2DXPoint(Camera::getInstance()->cameraX / 2 - 125, Camera::getInstance()->cameraY / 2 - 95), "PLAYER");
	drawText(enemy, M2DXPoint(Camera::getInstance()->cameraX / 2 - 125, Camera::getInstance()->cameraY / 2 - 80), "ENEMY");
	drawText(timeText, M2DXPoint(Camera::getInstance()->cameraX / 2 - 15, Camera::getInstance()->cameraY / 2 - 110), "TIME");
	drawText(stageText, M2DXPoint(Camera::getInstance()->cameraX / 2 + 65, Camera::getInstance()->cameraY / 2 - 110), "STAGE");
	//
	heartImage.setPosition(M2DXPoint(Camera::getInstance()->cameraX / 2 + 41, Camera::getInstance()->cameraY / 2 - 95));
	heartImage.draw();
	P.setPosition(M2DXPoint(Camera::getInstance()->cameraX / 2 + 41, Camera::getInstance()->cameraY / 2 - 80));
	P.draw();
	rect.setPosition(M2DXPoint(Camera::getInstance()->cameraX / 2, Camera::getInstance()->cameraY / 2 - 90));
	rect.draw();
	wepon->Draw();
	//
	drawNumber(score);
	drawNumber(time);
	drawNumber(stage);
	drawNumber(heart);
	drawNumber(Pre);
	drawBlood();
}
