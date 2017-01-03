#pragma once

class GetWepon
{
private:
	static GetWepon* _instance;
public:
	static GetWepon* getInstance()
	{
		if (!_instance)
		{
			_instance = new GetWepon();
		}
		return _instance;
	};
	int wepon = 1;
};
