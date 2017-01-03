#include "Thorns.h"
#include "SimonBelmont.h"


Thorns::Thorns(int X, int Y) : CObject(47, X, Y, THORNS_WIDTH, THORNS_HEIGHT, 0)
{
	distance = 0;
	_vy = THORNS_Y;
	remainingDraw = TIME_TO_DRAW;
	positionY = Y;
	initWithTexture("Resources\\Sprites\\Thorns\\Thorns");
	setPosition(M2DXPoint(_x / 2 - 3, _y / 2));
}

void Thorns::Update(int DeltaTime)
{
	swept->delta = DeltaTime;
	updatePosition(DeltaTime);
	updateState(DeltaTime);
	updateInfor(DeltaTime);
	updateChain();
}

bool Thorns::updateCollis(CObject * Ob)
{
	if (!isDead)
	{
		swept->CheckCollision(_box, Ob->_box);
		if (swept->direc != SweptAABB::Direction::None)
		{
			switch (Ob->_type)
			{
			case 2:
			{
				if (swept->direc == SweptAABB::Direction::Bottom)
				{
					_vy = -THORNS_Y/2;
				}
			}
			break;
			}
		}
	}
	return false;
}

void Thorns::updateChain()
{
	n = (getPositionY() - positionY) / 4 + 1;
	chain = new M2DXBaseSprite[n];
	for (int i = 0;i < n;i++)
	{
		chain[i].setTexture(M2DXResourceManager::getInstance()->getTextureByName("Resources\\Sprites\\Thorns\\Chain"));
		chain[i].setPosition(M2DXPoint(getPositionX() + 12, positionY + i * 4));
		chain[i].setFlipX(false);
	}
}

void Thorns::updateState(int deltaTime)
{
	if (getPositionY() < positionY)
		_vy = THORNS_Y;
}

void Thorns::updatePosition(int deltaTime)
{
	if (_vy > 0)
		distance = 0;
	distance += _vy * deltaTime;
	if (_vy < 0)
	{
		if (remainingDraw > 0)
		{
			remainingDraw -= 1;
			return;
		}
		else
			remainingDraw = 1;
	}
	auto positionY = getPositionY() + distance;
	setPositionY(positionY);
	distance = 0;
}

void Thorns::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_box.x = _x;
	_box.y = _y;
	_box.vy = _vy;
	_box.vx = 0;
}

void Thorns::Draw()
{
	for (int i = 0;i < n;i++)
		chain[i].draw();
	M2DXBaseSprite::draw();
}