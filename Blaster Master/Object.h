#pragma once
#include <math.h>
#include <vector>

#include "Animation.h"
#include "Debug.h"
#include "Texture.h"
#include "EnumConstant.h"
#include "Global.h"


using namespace std;


class Object
{
protected:
	LPD3DXVECTOR2 wAcceleration;
	LPD3DXVECTOR2 wVelocity;
	LPD3DXVECTOR2 wPosition;
	LPD3DXVECTOR2 move;
	double width, height;
	double friction;
	LPANIMATIONS animations;
	bool isExist;
	double t;
	int status;

public:
	Object();
	void SetVelocity(D3DXVECTOR2 velocity);
	void SetAcceleration(D3DXVECTOR2 acceleration);
	void SetCenterPostion(D3DXVECTOR2 center);
	void SetBottomPostion(D3DXVECTOR2 bottom);
	void SetTopPostion(D3DXVECTOR2 top);
	void SetLeftPostion(D3DXVECTOR2 left);
	void SetRightPostion(D3DXVECTOR2 right);

	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetAcceleration();
	D3DXVECTOR2 GetCenterPostion();
	D3DXVECTOR2 GetBottomPostion();
	D3DXVECTOR2 GetTopPostion();
	D3DXVECTOR2 GetLeftPostion();
	D3DXVECTOR2 GetRightPostion();
	LPD3DXVECTOR2 GetMove();
	LPD3DXVECTOR2 GetPosition();
	double GetWidth();
	double GetHeight();
	RECT GetCollisionBox();
	RECT GetHitBox();
	int GetStatus();
	bool IsExist();

	virtual void Init();
	virtual void Physical(DWORD dt);
	virtual void Update(DWORD dt);
	virtual void Render();
};

typedef Object* LPOBJECT;
