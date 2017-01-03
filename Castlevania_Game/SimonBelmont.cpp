#include "SimonBelmont.h"
#include "BloodManager.h"
#include "GetWepon.h"
#include "Stage.h"
#include "Camera.h"
#include "PauseScene.h"
#include "SceneManager.h"

SimonBelmont::SimonBelmont(int X, int Y) : actionState(Standing), CObject(1, X, Y , 32, 64, 0)
{
	initWithTexture(SIMON_BELMONT_TEXTURE_NAME);
	setPosition(M2DXPoint(X,Y));
	inverseColorAlpha = 1;
	timeInvulnerable = 0;
	isInvulnerable = false;
	remainingTimeToGetDamage = 0;
	remainingGettingDamagedTime = 1;
	colorAlpha = 255;
	gravity = GRAVITY;
	canWalkUp = false;
	canWalkDown = false;
	actionState = Standing;
	attackState = None;
	remainingGetMorningStar = 0;
	remainingChangeColor = 1;
}

SimonBelmont::~SimonBelmont()
{

}

void SimonBelmont::autoRun()
{
	if (!getFlipX())
		walk(Direction::Right);
	else
		walk(Direction::Left);
}

void SimonBelmont::getMorningStar(int deltaTime)
{
	if (remainingGetMorningStar > 0)
	{
		remainingGetMorningStar -= deltaTime;
		if (remainingChangeColor > 0)
		{
			remainingChangeColor -= 1;
			Stage::getInstance()->pauseGame = true;
			colorR = 66;
			colorG = 110;
			colorB = 180;
		}
		else
		{
			colorR = 229;
			colorG = 70;
			colorB = 70;
			remainingChangeColor = 1;
		}
	}
	else
	{
		if (remainingGetPotion <= 0)
		{
			colorR = 255;
			colorG = 255;
			colorB = 255;
		}
		Stage::getInstance()->pauseGame = false;
	}
}

void SimonBelmont::draw()
{
	D3DXCOLOR color;
	color = D3DCOLOR_ARGB(colorAlpha, colorR, colorG, colorB);
	M2DXAnimatedSprite::draw(color);
}

int SimonBelmont::getAnimateRate()
{
	switch (actionState)
	{
	case SimonBelmont::Standing:
		return SIMON_BELMONT_DEFAULT_ANIMATE_RATE;
	case SimonBelmont::Walking:
		return SIMON_BELMONT_WALKING_ANIMATE_RATE;
	case SimonBelmont::Kneeling:
		return SIMON_BELMONT_DEFAULT_ANIMATE_RATE;
	case SimonBelmont::Jumping:
		return SIMON_BELMONT_DEFAULT_ANIMATE_RATE;
	case SimonBelmont::StairStanding:
		return SIMON_BELMONT_DEFAULT_ANIMATE_RATE;
	case SimonBelmont::StairWalking:
		return SIMON_BELMONT_STAIR_WALKING_ANIMATE_RATE;
	case SimonBelmont::GettingDamaged:
		return SIMON_BELMONT_GETTING_DAMAGED_RATE;
	case SimonBelmont::Dead:
		return SIMON_BELMONT_DEFAULT_ANIMATE_RATE;
	default:
		break;
	}
}

void SimonBelmont::getPotion(int deltaTime)
{
	if (remainingGetPotion > 0)
	{
		isInvulnerable = true;
		remainingGetPotion -= deltaTime;
		colorR = 197;
		colorG = 124;
		colorB = 172;
	}
	else
	{
		if (remainingTimeToGetDamage <= 0)
			isInvulnerable = false;
		colorR = 255;
		colorG = 255;
		colorB = 255;
	}
}

void SimonBelmont::autoMove(int X)
{
	if (std::abs(_x - X) <= SIMON_BELMONT_WALKING_SPEED * 60)
	{
		setPositionX((float)X / 2);
		velocity.x = 0;
		velocity.y = 0;
		if (stairDirection == Direction::Left)
			setFlipX(true);
		else
			setFlipX(false);
		return;
	}
	if (_x < X)
		walk(Direction::Right);
	if (_x > X)
		walk(Direction::Left);
	if (_x == X)
	{
		if (stairDirection == Direction::Left)
			setFlipX(true);
		else
			setFlipX(false);
		return;
	}
}

void SimonBelmont::updateInfor(int deltaTime)
{
	_x = getPositionX() * 2;
	_y = getPositionY() * 2;
	_width = getSize().width * 2;
	_height = getSize().height * 2;
	_vx = velocity.x;
	_vy = velocity.y;
	_box.x = _x;
	_box.y = _y;
	_box.w = _width;
	_box.h = _height;
	_box.vx = _vx;
	_box.vy = _vy;
}

int SimonBelmont::updateColor(int deltaTime)
{
	if (remainingTimeToGetDamage > 0)
	{
		remainingTimeToGetDamage -= deltaTime;
		remainingGettingDamagedTime -= 1;
		if (remainingGettingDamagedTime < 0)
		{
			if (colorAlpha == 255)
				colorAlpha = 100;
			else
				colorAlpha = 255;
			remainingGettingDamagedTime = 1;
		}
	}
	else
	{
		colorAlpha = 255;
		isInvulnerable = false;
	}
	getPotion(deltaTime);
	getMorningStar(deltaTime);
	return 0;
}

string SimonBelmont::getNextFrame()
{
	auto currentFrame = getCurrentFrame();

	if (attackState == None)
	{
		switch (actionState)
		{
		case SimonBelmont::Standing:
			return SIMON_BELMONT_STANDING_FRAME_NAME;
		case SimonBelmont::Walking:
		{
			if (currentFrame == SIMON_BELMONT_STANDING_FRAME_NAME || currentFrame == SIMON_BELMONT_WALKING_FRAME_NAME_0)
			{
				return SIMON_BELMONT_WALKING_FRAME_NAME_1;
			}
			if (currentFrame == SIMON_BELMONT_WALKING_FRAME_NAME_1)
			{
				return SIMON_BELMONT_WALKING_FRAME_NAME_2;
			}
			else if (currentFrame == SIMON_BELMONT_WALKING_FRAME_NAME_2)
			{
				return SIMON_BELMONT_WALKING_FRAME_NAME_3;
			}
			else
			{
				return SIMON_BELMONT_WALKING_FRAME_NAME_0;
			}
		}
		case SimonBelmont::Kneeling:
			return SIMON_BELMONT_KNEELING_FRAME_NAME;
		case SimonBelmont::GettingDamaged:
				return SIMON_BELMONT_GETTING_DAMAGED;
		case SimonBelmont::Jumping:
			if (velocity.y <= -0.0078125)
			{
				return SIMON_BELMONT_KNEELING_FRAME_NAME;
			}
			else
			{
				return SIMON_BELMONT_STANDING_FRAME_NAME;
			}
		case StairStanding:
			switch (currentStairDirection)
			{
			case SimonBelmont::Up:
				return SIMON_BELMONT_WALKING_UP_FRAME_NAME_0;
			case SimonBelmont::Down:
				return SIMON_BELMONT_WALKING_DOWN_FRAME_NAME_0;
				break;
			default:
				break;
			}
		case StairWalking:
			switch (currentStairDirection)
			{
			case SimonBelmont::Up:
				if (currentFrame == SIMON_BELMONT_WALKING_UP_FRAME_NAME_0)
				{
					return SIMON_BELMONT_WALKING_UP_FRAME_NAME_1;
				}
				else
				{
					return SIMON_BELMONT_WALKING_UP_FRAME_NAME_0;
				}
				break;
			case SimonBelmont::Down:
				if (currentFrame == SIMON_BELMONT_WALKING_DOWN_FRAME_NAME_0)
				{
					return SIMON_BELMONT_WALKING_DOWN_FRAME_NAME_1;
				}
				else
				{
					return SIMON_BELMONT_WALKING_DOWN_FRAME_NAME_0;
				}
				break;
			default:
				break;
			}
			break;
		case SimonBelmont::ActionState::EnteringCastle:
			return SIMON_BELMONT_ENTERING_CASTLE;
			break;
		case SimonBelmont::Dead:
			return SIMON_BELMONT_DYING;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (attackState)
		{
		case SimonBelmont::Begin:
			switch (actionState)
			{
			case SimonBelmont::Standing:
			case SimonBelmont::Jumping:
				return SIMON_BELMONT_ATTACKING_FRAME_NAME_BEGIN;
			case SimonBelmont::Kneeling:
				return SIMON_BELMONT_ON_KNEEL_ATTACKING_BEGIN;
			case SimonBelmont::StairStanding:
				switch (currentStairDirection)
				{
				case SimonBelmont::Up:
					return SIMON_BELMONT_ON_WALKING_UP_ATTACKING_BEGIN;
				case SimonBelmont::Down:
					return SIMON_BELMONT_ON_WALKING_DOWN_ATTACKING_BEGIN;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		case SimonBelmont::Middle:
			switch (actionState)
			{
			case SimonBelmont::Standing:
				return SIMON_BELMONT_ATTACKING_FRAME_NAME_MIDDLE;
			case SimonBelmont::Kneeling:
				return SIMON_BELMONT_ON_KNEEL_ATTACKING_MIDDLE;
			case SimonBelmont::Jumping:
				return SIMON_BELMONT_ATTACKING_FRAME_NAME_MIDDLE;
			case SimonBelmont::StairStanding:
				switch (currentStairDirection)
				{
				case SimonBelmont::Up:
					return SIMON_BELMONT_ON_WALKING_UP_ATTACKING_MIDDLE;
				case SimonBelmont::Down:
					return SIMON_BELMONT_ON_WALKING_DOWN_ATTACKING_MIDDLE;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		case SimonBelmont::End:
			switch (actionState)
			{
			case SimonBelmont::Standing:
				return SIMON_BELMONT_ATTACKING_FRAME_NAME_END;
			case SimonBelmont::Kneeling:
				return SIMON_BELMONT_ON_KNEEL_ATTACKING_END;
			case SimonBelmont::Jumping:
				return SIMON_BELMONT_ATTACKING_FRAME_NAME_END;
			case SimonBelmont::StairStanding:
				switch (currentStairDirection)
				{
				case SimonBelmont::Up:
					return SIMON_BELMONT_ON_WALKING_UP_ATTACKING_END;
				case SimonBelmont::Down:
					return SIMON_BELMONT_ON_WALKING_DOWN_ATTACKING_END;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void SimonBelmont::update(int deltaTime)
{
	swept->delta = deltaTime;

	updateColor(deltaTime);

	if (remainingGetMorningStar <= 0)
	{
		updateActionState(deltaTime);

		updateAttackState(deltaTime);

		updateFrame(deltaTime);

		updateVelocity(deltaTime);

		updatePosition(deltaTime);
	}

	updateInfor(deltaTime);
}

void SimonBelmont::updateActionState(int deltaTime)
{
	switch (actionState)
	{
	case SimonBelmont::Standing:
		if (BloodManager::getInstance()->bloodSimon <= 0)
		{
			setPositionY(getPositionY()  + 16);
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
		}
		break;
	case SimonBelmont::Walking:
		if (BloodManager::getInstance()->bloodSimon <= 0)
		{
			setPositionY(getPositionY() + 16);
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
		}
		break;
	case SimonBelmont::Kneeling:
		if (BloodManager::getInstance()->bloodSimon <= 0)
		{
			setPositionY(getPositionY() + 8);
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
		}
		break;
	case SimonBelmont::Jumping:
		if (_y + _height  > Camera::getInstance()->getBound().bottom)
		{
			setPositionY(getPositionY() + 16);
			BloodManager::getInstance()->bloodSimon = 0;
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
		}
		break;
	case SimonBelmont::StairStanding:
		if (BloodManager::getInstance()->bloodSimon <= 0)
		{
			setPositionY(getPositionY() + 8);
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
		}
		break;
	case SimonBelmont::StairWalking:
		if (BloodManager::getInstance()->bloodSimon <= 0)
		{
			setPositionY(getPositionY() + 8);
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
			return;
		}
		if (isUpArrow == false && isDownArrow == false)
		{
			if (setNextStair == false)
			{
				int stair = std::abs(getPositionY() + 32 - stairPositionY);
				if (currentStairDirection == StairDirection::Up)
				{
					if (stairPositionY  > (getPositionY() + 32))
					nextStair = (getPositionY() + 32) - (8 - (stair % 8));
					else
						nextStair = (getPositionY() + 32) - ((stair % 8));
				}
				else
				{
					if (stairPositionY  > (getPositionY() + 32))
					nextStair = (getPositionY() + 32) + (stair % 8);
					else
						nextStair = (getPositionY() + 32) + (8-(stair % 8));
				}
				setNextStair = true;
			}
			if (getPositionY() + 32 != nextStair && canWalkToStair == true)
			{
				float distanceY = nextStair - (getPositionY() + 32);
				if (std::abs(velocity.y*deltaTime) >= std::abs(distanceY))
				{
					if (currentStairDirection == StairDirection::Down)
					{
						if (getFlipX())
							setPosition(M2DXPoint(getPositionX() - std::abs(distanceY), getPositionY() + std::abs(distanceY)));
						else
							setPosition(M2DXPoint(getPositionX() + std::abs(distanceY), getPositionY() + std::abs(distanceY)));
					}
					else
					{
						if (getFlipX() == false)
						setPosition(M2DXPoint(getPositionX() + std::abs(distanceY), getPositionY() - std::abs(distanceY)));
						else
							setPosition(M2DXPoint(getPositionX() - std::abs(distanceY), getPositionY() - std::abs(distanceY)));
					}
					actionState = StairStanding;
					velocity.x = 0;
					velocity.y = 0;
				}
				else
				{
					if (currentStairDirection == StairDirection::Down)
					{
						velocity.y = SIMON_BELMONT_STAIR_WALKING_SPEED;
					}
					else
					{
						velocity.y = -SIMON_BELMONT_STAIR_WALKING_SPEED;
					}
					if (getFlipX())
						velocity.x = -SIMON_BELMONT_STAIR_WALKING_SPEED;
					else
						velocity.x = SIMON_BELMONT_STAIR_WALKING_SPEED;
				}
			}
			else
			{
				actionState = StairStanding;
			}
		}
		break;
	case SimonBelmont::GettingDamaged:
		if (_y + _height  > Camera::getInstance()->getBound().bottom)
		{
			setPositionY(getPositionY() + 16);
			BloodManager::getInstance()->bloodSimon = 0;
			actionState = SimonBelmont::Dead;
			remainingReturnPrePont = RETURN_PRE_PONT;
		}
		break;
	case SimonBelmont::Dead:
		if (remainingReturnPrePont > 0)
		{
			M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Life_Lost"));
			remainingReturnPrePont -= deltaTime;
		}
			else
			{
				Stage::getInstance()->life -= 1;
				if (Stage::getInstance()->life >= 0)
				{
					BloodManager::getInstance()->bloodSimon = 16;
					setPositionX(Stage::getInstance()->prePointX);
					setPositionY(Stage::getInstance()->prePointY);
					setFlipX(Stage::getInstance()->flip);
					actionState = Standing;
					velocity.x = 0;
					velocity.y = 0;
					Camera::getInstance()->flat = getPositionY() / 240;
				}
				else
				{
					if (Stage::getInstance()->nextLevel == 1)
						M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\map1"));
					else
						M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\map2"));
					if (Camera::getInstance()->cameraX == Camera::getInstance()->BossX 
						&& Camera::getInstance()->cameraY == Camera::getInstance()->BossY)
						M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\Boss"));
						SceneManager::getInstance()->ReplaceBy(new PauseScene());
				}
			}
		break;
	default:
		break;
	}
}

void SimonBelmont::updateAttackState(int deltaTime)
{
	if (actionState == GettingDamaged || actionState == ActionState::Dead)
		attackState = None;
	if (attackState != None)
	{
		remainingAttackStateTime -= deltaTime;
		if (remainingAttackStateTime <= 0)
		{
			switch (attackState)
			{
			case SimonBelmont::Begin:
				attackState = Middle;
				break;
			case SimonBelmont::Middle:
			{
				switch (lastUsedWeapon)
				{
				case SimonBelmontAxe:
					WeponManager::getInstance()->AddElement((CObject*)new Axe(getHandPosition().x, getHandPosition().y , getFlipX()));
					break;
				case SimonBelmontBomerang:
					WeponManager::getInstance()->AddElement((CObject*)new Bomerang(getHandPosition().x, getHandPosition().y, getFlipX()));
					break;
				case SimonBelmontHolyWater:
					WeponManager::getInstance()->AddElement((CObject*)new HolyWater(getHandPosition().x, getHandPosition().y, getFlipX()));
					break;
				case SimonBelmontDagger:
					break;
				default:
					break;
				}
				attackState = End;
			}
				break;
			case SimonBelmont::End:
				switch (lastUsedWeapon)
				{
				case SimonBelmontDagger:
					WeponManager::getInstance()->AddElement((CObject*)new Dagger(getHandPosition().x, getHandPosition().y - 5, getFlipX()));
					break;
				case SimonBelmontWatch:
					WeponManager::getInstance()->AddElement((CObject*)new Watch());
					break;
				default:
					break;
				}
				attackState = None;
				break;
			default:
				break;
			}

			remainingAttackStateTime = ATTACK_STATE_TIME;
		}
	}
}

void SimonBelmont::updateVelocity(int deltaTime)
{
	if (actionState == Jumping || actionState == GettingDamaged)
	{
		velocity.y += gravity * deltaTime;
	}
}

void SimonBelmont::updatePosition(int deltaTime)
{
	if (actionState == Walking || actionState == Jumping || actionState == StairWalking || actionState == GettingDamaged)
	{
		auto position = getPosition();
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
		if (position.x < lockLeft/2)
			position.x = lockLeft/2 + 1;
		if (position.x + getSize().width > lockRight/2)
			position.x = lockRight / 2 - getSize().width + 1;
		setPosition(position);
	}
}

void SimonBelmont::command(SimonArrowsCommand arrowsCommand)
{
	if (attackState == None)
	{
		isUpArrow = arrowsCommand.upArrow;
		isDownArrow = arrowsCommand.downArrow;
		switch (actionState)
		{
		case SimonBelmont::Dead:
			break;
		case SimonBelmont::GettingDamaged:
			break;
		case SimonBelmont::Standing:
			if (!arrowsCommand.leftArrow && !arrowsCommand.rightArrow)
			{
				stopWalking();
			}

			if (arrowsCommand.leftArrow)
			{
				walk(Left);
			}

			if (arrowsCommand.rightArrow)
			{
				walk(Right);
			}

			if (arrowsCommand.downArrow)
			{
				if (canWalkDown == true)
				{
					if (getFlipX() == true)
					{
						walkDown(Left);
					}
					else
					{
						walkDown(Right);
					}
				}
				else
				kneel();
			}

			if (arrowsCommand.upArrow)
			{
				if (canWalkUp)
				{
					walkToStair();
					if (getFlipX())
					{
						walkUp(Left,stairPositionX);
					}
					else
					{
						walkUp(Right, stairPositionX);
					}
				}
			}
			break;
		case SimonBelmont::Walking:
			if (!arrowsCommand.leftArrow && !arrowsCommand.rightArrow && autoWalking == false)
			{
				stopWalking();
			}

			if (arrowsCommand.leftArrow)
			{
				walk(Left);
			}

			if (arrowsCommand.rightArrow)
			{
				walk(Right);
			}

			if (arrowsCommand.upArrow)
			{
				if (canWalkUp)
				{
					walkToStair();
					if (getFlipX())
					{
						walkUp(Left, stairPositionX);
					}
					else
					{
						walkUp(Right, stairPositionX);
					}
				}
			}
			if (arrowsCommand.downArrow)
			{
				if (canWalkDown)
				{
					walkToStair();
					if (getFlipX())
					{
						walkDown(Left);
					}
					else
					{
						walkDown(Right);
					}
				}
			}
			break;
		case SimonBelmont::Kneeling:
			if (!arrowsCommand.downArrow)
			{
				standUp();
			}

			if (arrowsCommand.leftArrow)
			{
				turn(Left);
			}

			if (arrowsCommand.rightArrow)
			{
				turn(Right);
			}
			break;
		case SimonBelmont::Jumping:
			break;
		case SimonBelmont::StairStanding:
			if (arrowsCommand.downArrow)
			{
				switch (currentStairDirection)
				{
				case SimonBelmont::Up:
					if (getFlipX())
					{
						walkDown(Right);
					}
					else
					{
						walkDown(Left);
					}
					break;
				case SimonBelmont::Down:
					if (getFlipX())
					{
						walkDown(Left);
					}
					else
					{
						walkDown(Right);
					}
					break;
				default:
					break;
				}
			}
			if (arrowsCommand.upArrow)
			{
				switch (currentStairDirection)
				{
				case SimonBelmont::Up:
					if (getFlipX())
					{
						walkUp(Left, stairPositionX);
					}
					else
					{
						walkUp(Right, stairPositionX);
					}
					break;
				case SimonBelmont::Down:
					if (getFlipX())
					{
						setFlipX(false);
						walkUp(Right, stairPositionX);
					}
					else
					{
						setFlipX(true);
						walkUp(Left, stairPositionX);
					}
					break;
				default:
					break;
				}
			}
		case SimonBelmont::StairWalking:
			break;
		default:
			break;
		}
	}
}

void SimonBelmont::command(int keyCode, bool upArrow)
{
	if (attackState == None)
	{
		switch (keyCode)
		{
		case JUMP_KEY_CODE:
			if (actionState == Standing || actionState == Walking)
			{
				jump();
			}
			break;
		case ATTACK_KEY_CODE:
			if (actionState != ActionState::Dead)
			{
				if (actionState != ActionState::StairWalking && actionState != ActionState::GettingDamaged)
				{
					attack();

					if (upArrow)
					{
						switch (GetWepon::getInstance()->wepon)
						{
						case 2:
						{
							currentWepon = SimonBelmontWeaponType::SimonBelmontBomerang;
						}
						break;
						case 3:
						{
							currentWepon = SimonBelmontWeaponType::SimonBelmontHolyWater;
						}
						break;
						case 4:
						{
							currentWepon = SimonBelmontWeaponType::SimonBelmontDagger;
						}
						break;
						case 5:
						{
							currentWepon = SimonBelmontWeaponType::SimonBelmontWatch;
						}
						break;
						case 1:
						{
							currentWepon = SimonBelmontWeaponType::SimonBelmontAxe;
						}
						break;
						default:
							break;
						}
						lastUsedWeapon = currentWepon;
					}
					else
					{
						WeponManager::getInstance()->AddElement((CObject*)new Whip(Stage::getInstance()->levelWhip));
						lastUsedWeapon = SimonBelmontWhip;
					}
				}
			}
			break;
		case CHANGE_WEPON_KEY_CODE:
		{
			switch (currentWepon)
			{
			case SimonBelmontWeaponType::SimonBelmontAxe:
			{
				currentWepon = SimonBelmontWeaponType::SimonBelmontBomerang;
				GetWepon::getInstance()->wepon = 2;
			}
			break;
			case SimonBelmontWeaponType::SimonBelmontBomerang:
			{
				currentWepon = SimonBelmontWeaponType::SimonBelmontHolyWater;
				GetWepon::getInstance()->wepon = 3;
			}
			break;
			case SimonBelmontWeaponType::SimonBelmontHolyWater:
			{
				currentWepon = SimonBelmontWeaponType::SimonBelmontDagger;
				GetWepon::getInstance()->wepon = 4;
			}
				break;
			case SimonBelmontWeaponType::SimonBelmontDagger:
			{
				currentWepon = SimonBelmontWeaponType::SimonBelmontWatch;
				GetWepon::getInstance()->wepon = 5;
			}
			break;
			case SimonBelmontWeaponType::SimonBelmontWatch:
			{
				currentWepon = SimonBelmontWeaponType::SimonBelmontAxe;
				GetWepon::getInstance()->wepon = 1;
			}
			break;
			default:
				break;
			}
			M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\decreaseweaponusepoint"));
		}
			break;
		default:
			break;
		}
	}
}

void SimonBelmont::gettingdamaged()
{
	if (actionState != ActionState::StairStanding && actionState != ActionState::StairWalking)
	{
		if (getFlipX())
		{
			velocity.x = SIMON_BELMONT_WALKING_SPEED;
		}
		else
			velocity.x = -SIMON_BELMONT_WALKING_SPEED;
		velocity.y = -SIMON_BELMONT_JUMPING_SPEED / 2;
		actionState = GettingDamaged;
	}
	isInvulnerable = true;
	remainingGettingDamagedTime = 2;
	remainingTimeToGetDamage = TIME_TO_GET_DAMAGE;
}

void SimonBelmont::walk(Direction direction)
{
	velocity.y = 0;
	if (direction == Left )
	{
		velocity.x = -SIMON_BELMONT_WALKING_SPEED;
	}
	else
		if(direction == Right)
	{
		velocity.x = SIMON_BELMONT_WALKING_SPEED;
	}

	actionState = Walking;

	setFlipX(direction == Left);
}

void SimonBelmont::stopWalking()
{
	velocity.x = 0;

	actionState = Standing;
}

void SimonBelmont::kneel()
{
	velocity.x = 0;
	auto positionY = getPositionY();
	positionY += SIMON_STANDING_HEIGHT - SIMON_KNEELING_HEIGHT;
	actionState = Kneeling;
	setPositionY(positionY);
}

void SimonBelmont::standUp()
{
	auto positionY = getPositionY();
	positionY -= SIMON_STANDING_HEIGHT - SIMON_KNEELING_HEIGHT;
	setPositionY(positionY);

	actionState = Standing;
}

void SimonBelmont::turn(Direction direction)
{
	setFlipX(direction == Left);
}

void SimonBelmont::jump()
{
	canWalkDown = false;
	canWalkUp = false;	
	velocity.y = -SIMON_BELMONT_JUMPING_SPEED;
	actionState = Jumping;
}

void SimonBelmont::walkToStair()
{
	
}

void SimonBelmont::walkUp(Direction direction,int X)
{
	if ((actionState != ActionState::StairWalking && actionState != ActionState::StairStanding) && getPositionX() * 2 != stairPositionX)
	{
		autoMove(stairPositionX);
		direction = stairDirection;
	}
	else
	{
		if (actionState != ActionState::StairWalking && actionState != ActionState::StairStanding)
		{
			direction = stairDirection;
			if (stairDirection == Direction::Left)
				setFlipX(true);
			else
				setFlipX(false);
			canWalkToStair = true;			
		}
		velocity.y = -SIMON_BELMONT_STAIR_WALKING_SPEED;
		if (direction == Left)
		{
			velocity.x = -SIMON_BELMONT_STAIR_WALKING_SPEED;
		}
		else
		{
			velocity.x = SIMON_BELMONT_STAIR_WALKING_SPEED;
		}

		actionState = StairWalking;

		canWalkDown = true;

		currentStairDirection = Up;

		setNextStair = false;
	}
}

void SimonBelmont::walkDown(Direction direction)
{
	if ((actionState == ActionState::Walking || actionState == ActionState::Standing) && _x != stairPositionX)
	{
		autoMove(stairPositionX);
		direction = stairDirection;
	}
	else
	{
		if (actionState == ActionState::Walking || actionState == ActionState::Standing)
		{
			direction = stairDirection;
			if (stairDirection == Direction::Left)
				setFlipX(true);
			else
				setFlipX(false);
			canWalkToStair = true;
		}
		velocity.y = SIMON_BELMONT_STAIR_WALKING_SPEED;

		if (direction == Left)
		{
			velocity.x = -SIMON_BELMONT_STAIR_WALKING_SPEED;

			setFlipX(true);
		}
		else
		{
			velocity.x = SIMON_BELMONT_STAIR_WALKING_SPEED;

			setFlipX(false);
		}


		actionState = StairWalking;

		canWalkUp = true;

		currentStairDirection = Down;

		setNextStair = false;
	}
}

void SimonBelmont::attack()
{
	if (actionState == Walking)
	{
		stopWalking();
	}

	attackState = Begin;
	remainingAttackStateTime = ATTACK_STATE_TIME;
}

M2DXPoint SimonBelmont::getHandPosition()
{
	auto position = getPosition();
	auto flipX = getFlipX();
	auto size = getSize();

	switch (attackState)
	{
	case SimonBelmont::Begin:
		if (flipX)
		{
			position.x += size.width;
		}
		position.y += 8;
		break;
	case SimonBelmont::Middle:
		if (flipX)
		{
			position.x += size.width;
		}
		position.y += 5;
		break;
	case SimonBelmont::End:
		if (flipX)
		{
			position.x += 1;
		}
		else
		{
			position.x += size.width - 1;
		}
		position.y += 13;
		break;
	default:
		break;
	}

	if (actionState == Standing || actionState == Jumping)
	{
		position.y++;
	}

	return position;
}

bool SimonBelmont::updateCollis(CObject *Ob)
{
	if (actionState != SimonBelmont::Dead)
	{
		float nomalX, nomalY;
		SweptAABB *sweptTemp = new SweptAABB();
		/*Box temp(boxOb.x*2,boxOb.y*2)*/
		Box boxSimon(getPositionX() * 2, getPositionY() * 2, SimonBelmont::getSize().width * 2, SimonBelmont::getSize().height * 2, velocity.x, velocity.y + gravity * swept->delta);
		swept->CheckCollision(boxSimon, Ob->_box);
		sweptTemp->delta = swept->delta;
		sweptTemp->CheckCollision(Ob->_box, _box);
		if (swept->direc != SweptAABB::Direction::None && Ob->currentState == CObject::State::alive)
		{
			switch (Ob->_type)
			{
			case 2:
			{
				switch (swept->direc)
				{
				case SweptAABB::Direction::Bottom:
				{
					if (_y + _height)
					{
						if (actionState == ActionState::Jumping || (actionState == GettingDamaged && velocity.y > 0))
						{
							actionState = Standing;
						}
						if (actionState != StairStanding && actionState != StairWalking)
							setPositionY(Ob->_y / 2 - _height / 2);
					}
				}
				break;
				case SweptAABB::Direction::Top:
				{
				}
				break;
				case SweptAABB::Direction::Left:
				{
					if (actionState != StairWalking && actionState != StairStanding)
					{
						if (sweptTemp->direc == SweptAABB::Direction::Right)
							setPositionX(Ob->_x / 2 + Ob->_width / 2);
					}
				}
				break;
				case SweptAABB::Direction::Right:
				{
					if (actionState != StairWalking && actionState != StairStanding)
					{
						if (sweptTemp->direc == SweptAABB::Direction::Left)
							setPositionX(Ob->_x / 2 - _width / 2);
					}
				}
				break;
				}
			}
			break;
			//cầu thang đi lên bên phải
			case 14:
			{
				if (actionState == Standing || actionState == Walking)
				{
					stairPositionX = Ob->_x;
					stairPositionY = Ob->_y / 2 + 16;
					stairDirection = Direction::Right;
					//setPositionY(stairPositionY - 32);
					canWalkUp = true;
				}
				if ((actionState == StairStanding || actionState == StairWalking) && currentStairDirection == Down && ((_y + _height) - Ob->_y >= Ob->_height)
					&& getFlipX() == true)
				{
					canWalkToStair = false;
					actionState = Standing;
					setPositionX(Ob->_x / 2);
					canWalkUp = false;
					canWalkDown = false;
				}
			}
			break;
			//cầu thang đi xuống bên trái
			case 15:
			{
				if ((actionState == StairStanding || actionState == StairWalking) && currentStairDirection == Up && ((_y + _height) < (Ob->_y + Ob->_height))
					&& getFlipX() == false)
				{
					canWalkToStair = false;
					actionState = Standing;
					velocity.x = 0;
					velocity.y = 0;
					setPositionY(Ob->_y / 2 - 24);
					setPositionX(Ob->_x / 2);
					canWalkUp = false;
					canWalkDown = false;
				}
				else
					if ((actionState != StairStanding && actionState != StairWalking))
					{
						stairPositionX = Ob->_x;
						stairDirection = Direction::Left;
						canWalkDown = true;
					}
			}
			break;
			//cầu thang lên bên trái
			case 16:
			{
				if (actionState == Standing || actionState == Walking)
				{
					stairPositionX = Ob->_x;
					stairPositionY = Ob->_y / 2 + 16;
					//setPositionY(stairPositionY - 32);
					stairDirection = Direction::Left;
					canWalkUp = true;
				}
				if ((actionState == StairStanding || actionState == StairWalking) && currentStairDirection == Down && ((_y + _height) - Ob->_y >= Ob->_height)\
					&& getFlipX() == false)
				{
					canWalkToStair = false;
					actionState = Standing;
					setPositionX(Ob->_x / 2);
					canWalkUp = false;
					canWalkDown = false;
				}
			}
			break;
			//cầu thang xuong  bên phải
			case 17:
			{
				if ((actionState == StairStanding || actionState == StairWalking) && currentStairDirection == Up && ((_y + _height) < (Ob->_y + Ob->_height))
					&& getFlipX() == true)
				{
					canWalkToStair = false;
					actionState = Standing;
					velocity.x = 0;
					velocity.y = 0;
					setPositionY(Ob->_y / 2 - 24);
					setPositionX(Ob->_x / 2);
					canWalkUp = false;
					canWalkDown = false;
				}
				else
					if ((actionState != StairStanding && actionState != StairWalking))
					{
						stairPositionX = Ob->_x;
						stairDirection = Direction::Right;
						canWalkDown = true;
					}
			}
			break;
			case 5:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 8:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 9:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 7:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 6:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED && Ob->visible == true)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 3;
				}
			}
			break;
			case 4:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 11:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 3;
				}
			}
			break;
			case 13:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED && Ob->visible == true)
				{
					gettingdamaged();
					Ob->attacked = true;
					BloodManager::getInstance()->bloodSimon -= 3;
				}
			}
			break;
			case 18:
			{
				if (swept->direc == SweptAABB::Direction::Bottom && sweptTemp->direc == SweptAABB::Direction::Top)
				{
					setactionState(Standing);
					setPositionY(Ob->_y / 2 - _height / 2);
					setPositionX(getPositionX() + Ob->_box.vx*swept->delta);
				}
			}
			break;
			case 21:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 22:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 23:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 24:
			{
				if (isInvulnerable == false && Ob->getCurrentState() == State::alive && getCurrentFrame() != SIMON_BELMONT_GETTING_DAMAGED && visible == true)
				{
					gettingdamaged();
					BloodManager::getInstance()->bloodSimon -= 2;
				}
			}
			break;
			case 37:
			{
				switch (swept->direc)
				{
				case SweptAABB::Direction::Bottom:
				{
					if (_y + _height)
					{
						if (actionState == ActionState::Jumping || (actionState == GettingDamaged && velocity.y > 0))
						{
							actionState = Standing;
						}
						if (actionState != StairStanding && actionState != StairWalking)
							setPositionY(Ob->_y / 2 - _height / 2);
					}
				}
				break;
				case SweptAABB::Direction::Top:
				{
				}
				break;
				case SweptAABB::Direction::Left:
				{
					if (actionState != StairWalking && actionState != StairStanding)
					{
						if (sweptTemp->direc == SweptAABB::Direction::Right)
							setPositionX(Ob->_x / 2 + Ob->_width / 2);
					}
				}
				break;
				case SweptAABB::Direction::Right:
				{
					if (actionState != StairWalking && actionState != StairStanding)
					{
						if (sweptTemp->direc == SweptAABB::Direction::Left)
							setPositionX(Ob->_x / 2 - _width / 2);
					}
				}
				break;
				}
			}
			break;
			case 46:
			{
				if (Ob->visible == true)
				{
					Ob->isDead = true;
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\collectitem"));
					Score::getInstance()->score += 2000;
				}
			}
			break;
			case 35:
			{
				if (Ob->visible == true)
				{
					Ob->isDead = true;
					M2DXDSound::getInstance()->play(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\collectitem"));
					Score::getInstance()->score += 1000;
				}
			}
			break;
			case 47:
			{
				if (swept->direc == SweptAABB::Direction::Bottom || swept->direc == SweptAABB::Direction::Top)
					BloodManager::getInstance()->bloodSimon = 0;
			}
			break;
			}
			return true;
		}
	}
	return false;
}