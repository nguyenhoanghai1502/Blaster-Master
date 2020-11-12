#pragma once
#include"Object.h"
class Jumper : public Object
{
private:
	int direction;
	bool isWalking;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		WALKRIGHT,
		WALKLEFT,
		_lenght
	};

	Jumper();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();
	static Jumper* GetInstance();

	void IdleRight();
	void IdleLeft();
	void WalkLeft();
	void WalkRight();
	void Jump();
};
typedef Jumper* LPJUMPER;
