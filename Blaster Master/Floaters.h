#pragma once
#include"Object.h"
class Floaters : public Object {
private:
	int direction;
	int isdown;
public:
	enum ANIMATIONS
	{
		RIGHT,
		LEFT,
		_lenght
	};

	Floaters();
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();
	void FlyUp();
	void FlyDown();
};
typedef Floaters* LPFLOATER;

