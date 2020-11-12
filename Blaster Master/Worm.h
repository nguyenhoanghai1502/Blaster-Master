#pragma once
#include"Object.h"
class Worm : public Object
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

	Worm();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();
	static Worm* GetInstance();

	void IdleRight();
	void IdleLeft();
	void WalkLeft();
	void WalkRight();
	void Jump();
};
typedef Worm* LPWORM;

