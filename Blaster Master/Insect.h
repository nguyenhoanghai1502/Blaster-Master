#pragma once
#include"Object.h"
class Insect : public Object
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

	Insect();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();

	void FLYLeft();
	void FLYRight();
};
typedef Insect* LPInsect;


