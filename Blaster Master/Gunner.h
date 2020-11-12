#pragma once
#include"Object.h"
class Gunner : public Object
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

	Gunner();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();
	static Gunner* GetInstance();

	void IdleRight();
	void IdleLeft();
	void WalkLeft();
	void WalkRight();
	void Jump();
};
typedef Gunner* LPGUNNER;

