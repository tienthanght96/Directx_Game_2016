#pragma once
class Score
{
private:
	static Score* _instance ;
public:
	static Score* getInstance()
	{
		if (!_instance)
		{
			_instance = new Score();
		}
		return _instance;
	};
	int score = 0;
};
