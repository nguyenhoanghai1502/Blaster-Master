#pragma once
#include"Object.h"
class Domes : public Object
{
private:
	int direction;
	bool isWalking;
public:
	enum ANIMATIONS
	{
		WALKRIGHT,
		WALKLEFT,
		WALKUP,
		WALKDOWN,
		_lenght
	};

	Domes();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();


	void IdleRight();
	void IdleLeft();
	void WalkLeft();
	void WalkRight();
	void WalkUp();
	void WalkDown();
};
typedef Domes* LPDOMES;

