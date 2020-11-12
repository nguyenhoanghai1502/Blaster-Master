#include "Domes.h"
Domes::Domes()
{
	this->direction =1 ;
	this->isWalking = false;
}
void Domes::Init()
{
	LPTEXTURE tex = new Texture(L"textures/Enemies.png", D3DCOLOR_XRGB(0, 38, 255));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::WALKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(66, 423, 85, 439, d3dtex), 100);
			ani->Add(new Sprite(87, 424, 104, 439, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::WALKRIGHT);
			break;
		}
		case ANIMATIONS::WALKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(84, 479, 102, 498, d3dtex), 101);
			ani->Add(new Sprite(63, 479, 83, 498, d3dtex), 101);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKUP:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(45, 461, 64, 480, d3dtex), 600);
			ani->Add(new Sprite(45, 440, 64, 460, d3dtex), 600);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKDOWN:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(102, 440, 121, 459, d3dtex), 601);
			ani->Add(new Sprite(104, 461, 121, 479, d3dtex), 601);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	WalkRight();
}
void Domes::Update(DWORD dt)
{

	Physical(dt);
	if (wPosition->x < 1797)
	{
		WalkRight();
	}
	if (wPosition->x > 1967)
	{
		this->direction = -1;
		WalkLeft();
	}

	/*if (wPosition->y <= 1055&& wPosition->x>=1808)
	{
		WalkDown();
	}
	if (wPosition->y>= 1089&&wPosition->x>=1808)
	{
		WalkLeft();
	}
	if (wPosition->y >= 1089 && wPosition->x <= 1775)
	{
		WalkUp();
	}
	if (wPosition->y <= 1055 && wPosition->x <= 1775)
	{
		this->direction=-1;
	}*/
	if (animations != NULL)
		animations->Update(dt);
}
void Domes::Physical(DWORD dt)
{
	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Domes::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Domes::WalkLeft()
{
	this->status = Domes::ANIMATIONS::WALKRIGHT;
	int x = -0.05 * this->direction;
	this->SetVelocity(D3DXVECTOR2(-0.05, 0.00));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKRIGHT);
}
void Domes::WalkRight()
{
	this->status = Domes::ANIMATIONS::WALKRIGHT;
	int x = 0.05 * this->direction;
	this->SetVelocity(D3DXVECTOR2(0.05, 0.00));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKRIGHT);
}
void Domes::WalkUp()
{
	this->status = Domes::ANIMATIONS::WALKUP;
	int x = -0.05 * this->direction;
	this->SetVelocity(D3DXVECTOR2(0.00, x));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKUP);
}
void Domes::WalkDown()
{
	this->status = Domes::ANIMATIONS::WALKDOWN;
	int x = 0.05 * this->direction;
	this->SetVelocity(D3DXVECTOR2(0.00, x));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKDOWN);
}