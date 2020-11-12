#pragma once
#include <unordered_map>
#include "Activity.h"
#include "Object.h"


using namespace std;


class  WheelLeft : public Object
{
private:
	LPACTIVITIES activities;
public:
	enum ANIMATIONS
	{
		SPIN,
		_lenght
	};
	enum ACTIVITIES {
		SHRINK
	};
	WheelLeft();
	void Init();
	void Update(DWORD dt);
	void Render();

	void Idle();
	void SpinRight();
	void SpinLeft();
	void Shrink();
	void Indent();
	~WheelLeft();
};
typedef WheelLeft* LPWHEELLEFT;

class  WheelRight : public Object
{
private:
	LPACTIVITIES activities;

public:
	enum ANIMATIONS
	{
		SPIN,
		_lenght
	};
	enum ACTIVITIES {
		SHRINK
	};

	WheelRight();
	void Init();
	void Update(DWORD dt);
	void UpdateSpeedRotate(double speed);
	void Render();
	void Idle();
	void SpinRight();
	void SpinLeft();
	void Shrink();
	void Indent();
	~WheelRight();
};
typedef WheelRight* LPWHEELRIGHT;

class  Body : public Object
{
private:
	float a;//Biên độ
	bool isUndulating;
	LPACTIVITIES activities;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		_lenght
	};
	enum ACTIVITIES {
		UP_RIGHT,
		UP_LEFT
	};

	Body();
	void Init();
	void Update(DWORD dt);
	void Render();
	void IdleRight();
	void IdleLeft();

	void UpRight();
	void UpLeft();
	void DownRight();
	void DownLeft();
	void SetUndulate(bool isUndulating);
	void Physical(DWORD dt);
	~Body();
};
typedef Body* LPBODY;

class  Head : public Object
{
private:
	LPBODY body;
	LPACTIVITIES activities;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		ROTATERIGHT,
		ROTATELEFT,
		UPRIGHT,
		UPLEFT,
		OPENDOORRIGHT,
		OPENDOORLEFT,
		_lenght
	};
	enum ACTIVITIES {
		UP_RIGHT,
		UP_LEFT
	};

	enum STATUS
	{
		DOWN,
		UP,
		ROTATE
	};

	Head();
	void Init(LPBODY body);
	void Update(DWORD dt);
	void Render();

	void IdleRight();
	void IdleLeft();
	void RotateRight();
	void RotateLeft();
	void UpRight();
	void UpLeft();
	void DownRight();
	void DownLeft();
	void OpenDoorRight();
	void OpenDoorLeft();
	~Head();
};
typedef Head* LPHEAD;

class  Gun : public Object
{
private:
	LPBODY body;
	LPACTIVITIES activities;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		UPRIGHT,
		UPLEFT,
		_lenght
	};
	enum ACTIVITIES {
		UP_RIGHT,
		UP_LEFT
	};

	Gun();
	void Init(LPBODY body);
	void Update(DWORD dt);
	void Render();

	void IdleRight();
	void IdleLeft();

	void UpRight();
	void UpLeft();
	void DownRight();
	void DownLeft();
	~Gun();
};
typedef Gun* LPGUN;



class SOPHIA : public Object
{
private:
	static SOPHIA* _instance;
	LPWHEELLEFT wheelL;
	LPWHEELRIGHT wheelR;
	LPBODY body;
	LPHEAD head;
	LPGUN gun;
	int direction;
	D3DXVECTOR2 maxVelocity;
	bool isWalking;
	bool isControlling;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		WALKRIGHT,
		WALKLEFT,
		UPRIGHT,
		UPLEFT,
		OPENDOOR,
		_lenght
	};

	enum STATUS {
		IDLE,
		UP,
		UPTOIDLE,
		WALK,
		JUMP
	};

	SOPHIA();
	static SOPHIA* GetInstance();
	D3DXVECTOR2 GetMaxVelocity();
	bool IsAni(int aniid);
	int GetDirection();
	bool GetIsControlling();
	void SetIsControlling(bool _isControlling);
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();
	void ProcessKeyStates();
	void Stop();
	void IdleRight();
	void IdleLeft();
	void WalkLeft();
	void WalkRight();
	void Up();
	void Jump();
	void OpenDoor();

	void Down();
};
typedef SOPHIA* LPSOPHIA;

