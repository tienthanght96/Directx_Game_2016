#pragma once
class Stage
{
private:
	static Stage* _instance;
public:
	static Stage* getInstance()
	{
		if (!_instance)
		{
			_instance = new Stage();
		}
		return _instance;
	};
	int levelWhip = 0;
	int stage = 0;
	int nextLevel = 2;
	float prePointX;
	float prePointY;
	int life = 3;
	bool flip;
	bool pauseGame = false;
};
