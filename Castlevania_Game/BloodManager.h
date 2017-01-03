#pragma once
class BloodManager
{
private:
	static BloodManager* _instance;
public:
	static BloodManager* getInstance()
	{
		if (!_instance)
		{
			_instance = new BloodManager();
		}
		return _instance;
	};
	int bloodSimon = 16;
	int bloodEnemy = 16;
};
