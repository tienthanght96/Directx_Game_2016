#pragma once
class Time
{
private:
	static Time* _instance;
public:
	static Time* getInstance()
	{
		if (!_instance)
		{
			_instance = new Time();
		}
		return _instance;
	};
	int time = 400;
};
