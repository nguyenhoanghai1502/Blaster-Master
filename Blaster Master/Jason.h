#pragma once
#include "SOPHIA.h"

class Jason : public Object
{
private:
	static Jason* _instance;
	LPACTIVITIES activities;
	int direction;
	D3DXVECTOR2 maxVelocity;
	bool isControlling;
public:
	enum ANIMATIONS
	{
		IDLERIGHT,
		IDLELEFT,
		WALKRIGHT,
		WALKLEFT,
		DOWNRIGHT,
		DOWNLEFT,
		CRAWLRIGHT,
		CRAWLLEFT,
		JUMPRIGHT,
		JUMPLEFT,
		DIERIGHT,
		DIELEFT,
		JUMPOUTCARRIGHT,
		JUMPOUTCARLEFT,
		JUMPINCARRIGHT,
		JUMPINCARLEFT,
		_lenght
	};

	enum ACTIVITIES
	{
		JUMPOUTCARRIGHT_AC,
		JUMPOUTCARLEFT_AC,
		JUMPINCARRIGHT_AC,
		JUMPINCARLEFT_AC
	};

	enum STATUS
	{
		IDLE,
		WALK,
		JUMP,
		DOWN,
		CRAWL,
		DIE
	};

	Jason();
	bool IsAni(int aniid);
	void Init();
	void Update(DWORD dt);
	void Physical(DWORD dt);
	void Render();
	void ProcessKeyStates();
	bool GetIsControlling();
	void SetIsControlling(bool _isControlling);
	void Stop();

	void Idle();
	void WalkLeft();
	void WalkRight();
	void DownLeft();
	void DownRight();
	void JumpRight();
	void JumpLeft();
	void CrawlRight();
	void CrawlLeft();
	void DieRight();
	void DieLeft();
	void MoveRight();
	void MoveLeft();
	void StopMove();

	static Jason* GetInstance();
};
typedef Jason* LPJASON;

