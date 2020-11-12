#pragma once
#include"Object.h"
class Skulls : public Object
{
private:
	int direction;
	bool isWalking;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		FLYRIGHT,
		FLYLEFT,
		_lenght
	};

	Skulls();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();


	void IdleRight();
	void IdleLeft();
	void FLYLeft();
	void FLYRight();
};
typedef Skulls* LPSkulls;
