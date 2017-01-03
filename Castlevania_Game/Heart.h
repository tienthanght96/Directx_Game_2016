#pragma once
class Heart
{
private:
	static Heart* _instance;
public:
	static Heart* getInstance()
	{
		if (!_instance)
		{
			_instance = new Heart();
		}
		return _instance;
	};
	int heart = 0;
};
