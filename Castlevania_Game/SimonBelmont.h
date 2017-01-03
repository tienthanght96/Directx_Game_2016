#ifndef __SIMONBELMONT_H__
#define __SIMONBELMONT_H__

#include "m2dx.h"
#include "Whip.h"
#include "Axe.h"
#include "SweptAABB.h"
#include "Global.h"
#include "CObject.h"
#include "WeponManager.h"
#include "Bomerang.h"
#include "HolyWater.h"
#include "Dagger.h"
#include "Watch.h"

#ifndef SCALE_FACTOR
#define SCALE_FACTOR 2.0F
#endif

#ifndef GRAVITY
#define GRAVITY 0.00048828125F
#endif

#define SIMON_BELMONT_SPRITE_SHEET_PATH "Resources\\Sprites\\Simon Belmont\\SimonBelmontSpriteSheet.png"
#define SIMON_BELMONT_TEXTURE_NAME "Resources\\Sprites\\Simon Belmont\\SimonBelmontSpriteSheet"

#define SIMON_BELMONT_DEFAULT_ANIMATE_RATE 8
#define SIMON_BELMONT_WALKING_ANIMATE_RATE 6
#define	SIMON_BELMONT_GETTING_DAMAGED_RATE 10
#define SIMON_BELMONT_STAIR_WALKING_ANIMATE_RATE 8

#define SIMON_BELMONT_DYING "SimonBelmontDying"
#define SIMON_BELMONT_STANDING_FRAME_NAME "SimonBelmontStanding"
#define SIMON_BELMONT_WALKING_FRAME_NAME_0 "SimonBelmontWalking0"
#define SIMON_BELMONT_WALKING_FRAME_NAME_1 "SimonBelmontWalking1"
#define SIMON_BELMONT_WALKING_FRAME_NAME_2 "SimonBelmontWalking2"
#define SIMON_BELMONT_WALKING_FRAME_NAME_3 "SimonBelmontWalking3"
#define SIMON_BELMONT_KNEELING_FRAME_NAME "SimonBelmontKneeling"
#define SIMON_BELMONT_WALKING_UP_FRAME_NAME_0 "SimonBelmontWalkingUp0"
#define SIMON_BELMONT_WALKING_UP_FRAME_NAME_1 "SimonBelmontWalkingUp1"
#define SIMON_BELMONT_WALKING_DOWN_FRAME_NAME_0 "SimonBelmontWalkingDown0"
#define SIMON_BELMONT_WALKING_DOWN_FRAME_NAME_1 "SimonBelmontWalkingDown1"
#define SIMON_BELMONT_ATTACKING_FRAME_NAME_BEGIN "SimonBelmontAttackingBegin"
#define SIMON_BELMONT_ATTACKING_FRAME_NAME_MIDDLE "SimonBelmontAttackingMiddle"
#define SIMON_BELMONT_ATTACKING_FRAME_NAME_END "SimonBelmontAttackingEnd"
#define SIMON_BELMONT_ON_KNEEL_ATTACKING_BEGIN "SimonBelmontOnKneelAttackingBegin"
#define SIMON_BELMONT_ON_KNEEL_ATTACKING_MIDDLE "SimonBelmontOnKneelAttackingMiddle"
#define SIMON_BELMONT_ON_KNEEL_ATTACKING_END "SimonBelmontOnKneelAttackingEnd"
#define SIMON_BELMONT_ON_WALKING_DOWN_ATTACKING_BEGIN "SimonBelmontOnWalkingDownAttackingBegin"
#define SIMON_BELMONT_ON_WALKING_DOWN_ATTACKING_MIDDLE "SimonBelmontOnWalkingDownAttackingMiddle"
#define SIMON_BELMONT_ON_WALKING_DOWN_ATTACKING_END "SimonBelmontOnWalkingDownAttackingEnd"
#define SIMON_BELMONT_ON_WALKING_UP_ATTACKING_BEGIN "SimonBelmontOnWalkingUpAttackingBegin"
#define SIMON_BELMONT_ON_WALKING_UP_ATTACKING_MIDDLE "SimonBelmontOnWalkingUpAttackingMiddle"
#define SIMON_BELMONT_ON_WALKING_UP_ATTACKING_END "SimonBelmontOnWalkingUpAttackingEnd"
#define SIMON_BELMONT_GETTING_DAMAGED "SimonBelmontGettingDamaged"
#define SIMON_BELMONT_ENTERING_CASTLE "SimonBelmontEnteringCastle"

#define SIMON_STANDING_HEIGHT 32
#define SIMON_KNEELING_HEIGHT 24

#define SIMON_BELMONT_WALKING_SPEED 0.0625F
#define SIMON_BELMONT_JUMPING_SPEED 0.1875F
#define SIMON_BELMONT_STAIR_WALKING_SPEED 0.040625F

#define STAIR_STEP_TIME 150
#define ATTACK_STATE_TIME 100
#define GETTING_DAMAGED_TIME 300
#define TIME_TO_GET_DAMAGE 2000
#define RETURN_PRE_PONT 1000

#define JUMP_KEY_CODE DIK_Z
#define ATTACK_KEY_CODE DIK_X
#define CHANGE_WEPON_KEY_CODE DIK_C

class SimonBelmont : public M2DXAnimatedSprite, CObject
{
public:
	enum ActionState
	{
		Standing,
		Walking,
		Kneeling,
		Jumping,
		StairStanding,
		StairWalking,
		GettingDamaged,
		EnteringCastle,
		Dead
	};

	enum AttackState
	{
		None,
		Begin,
		Middle,
		End
	};

	enum SimonBelmontWeaponType
	{
		SimonBelmontWhip,
		SimonBelmontAxe,
		SimonBelmontBomerang,
		SimonBelmontHolyWater,
		SimonBelmontDagger,
		SimonBelmontWatch
	};

	struct SimonArrowsCommand
	{
		bool leftArrow = false;
		bool rightArrow = false;
		bool downArrow = false;
		bool upArrow = false;
	};

	enum Direction
	{
		Left,
		Right
	};

	enum StairDirection
	{
		Up,
		Down
	};

	SimonBelmont() {};
	SimonBelmont(int X, int Y);
	~SimonBelmont();
	bool autoWalking = false;
	void command(SimonArrowsCommand arrowsCommand);
	void command(int keyCode, bool upArrow);
	void update(int deltaTime);
	inline AttackState getAttackState() { return attackState; }
	bool updateCollis(CObject* Ob);
	void draw() override;
	M2DXPoint getHandPosition();
	inline ActionState getActionState() { return actionState; }
	inline void setactionState(ActionState action) { actionState = action; };
	void setSimonHealth(int m_health) { Health = m_health; };
	int getSimonHealth() { return Health; };
	void setLockLeft(int lock) { lockLeft = lock; };
	void setLockRight(int lock) { lockRight = lock; };
	void autoRun();
	int remainingGetMorningStar;
	void getMorningStar(int deltaTime);
	void gettingdamaged();
	int remainingGetPotion;
	void setCurrentWepons(SimonBelmontWeaponType type) { currentWepon = type; };
	StairDirection getStairDirection() { return currentStairDirection; };
	void reset()
	{
		canWalkDown = false;
		canWalkUp = false;
	};
protected:
	string getNextFrame() override;
	int getAnimateRate() override;

private:
	void getPotion(int deltaTime);
	SimonBelmontWeaponType currentWepon;
	int remainingChangeColor;
	int colorR, colorG, colorB;
	bool isUpArrow = false;
	bool isDownArrow = false;
	bool setNextStair = false;
	float nextStair;
	bool canWalkToStair = false;
	Direction stairDirection;
	void autoMove(int X);
	int stairPositionX;
	int stairPositionY;
	int lockLeft;
	int lockRight;
	int Health;
	void updateInfor(int deltaTime);
	int colorAlpha;
	int updateColor(int deltaTime);
	int inverseColorAlpha;
	int timeInvulnerable;
	bool isInvulnerable;
	int timeToSetColor;
	SweptAABB* swept = new SweptAABB();
	int deltatime;
	ActionState actionState;
	D3DXVECTOR2 velocity;
	float gravity;
	bool canWalkUp;
	bool canWalkDown;
	StairDirection currentStairDirection;
	int remainingStairStepTime;
	int remainingGettingDamagedTime;
	int remainingTimeToGetDamage;
	int remainingReturnPrePont;
	AttackState attackState;
	int remainingAttackStateTime;
	SimonBelmontWeaponType lastUsedWeapon;
	void updateActionState(int deltaTime);
	void updateAttackState(int deltaTime);
	void updateVelocity(int deltaTime);
	void updatePosition(int deltaTime);
	void walk(Direction direction);
	void stopWalking();
	void kneel();
	void standUp();
	void turn(Direction direction);
	void jump();
	void walkToStair();
	void walkUp(Direction direction, int X);
	void walkDown(Direction direction);
	void attack();
};

#endif