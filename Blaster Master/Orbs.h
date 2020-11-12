#pragma once
#include"Object.h"
class Orbs : public Object
{
private:
	int direction;
public:
	enum ANIMATIONS
	{
		TURN,
		FLYRIGHT,
		FLYLEFT,
		_lenght
	};

	Orbs();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();


	void FLYLeft();
	void FLYRight();
};
typedef Orbs* LPOrbs;

