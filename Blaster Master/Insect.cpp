#include "Insect.h"
Insect::Insect()
{
	this->direction = 1;
	this->isWalking = false;
}
void Insect::Init()
{
	LPTEXTURE tex = new Texture(L"textures/Enemies.png", D3DCOLOR_XRGB(0, 38, 255));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 530, 150, 548, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(102, 530, 121, 544, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 530, 150, 548, d3dtex), 600);
			ani->Add(new Sprite(151, 533, 170, 549, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(83, 532, 101, 548, d3dtex), 600);
			ani->Add(new Sprite(103, 529, 120, 548, d3dtex), 600);
			
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}
	FLYRight();
}
void Insect::Update(DWORD dt)
{

	Physical(dt);

	if (wPosition->x > 2000) {
		FLYLeft();
	}
	if (wPosition->x < 1800)
	{
		FLYRight();
	}

	if (animations != NULL)
		animations->Update(dt);
}
void Insect::Physical(DWORD dt)
{
	// Khi nhay len

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Insect::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Insect::FLYLeft()
{
	this->status = Insect::ANIMATIONS::FLYLEFT;
	this->SetVelocity(D3DXVECTOR2(-0.07, 0.00));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::FLYLEFT);
}
void Insect::FLYRight()
{
	this->status = Insect::ANIMATIONS::FLYRIGHT;
	this->SetVelocity(D3DXVECTOR2(0.07, 0.00));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::FLYRIGHT);

}
