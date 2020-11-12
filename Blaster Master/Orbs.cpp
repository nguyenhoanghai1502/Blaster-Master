#include "Orbs.h"
Orbs::Orbs()
{
	this->direction = 1;
}
void Orbs::Init()
{
	LPTEXTURE tex = new Texture(L"textures/Enemies.png", D3DCOLOR_XRGB(0, 38, 255));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::TURN:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(118, 387, 136, 405, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::TURN);
			break;
		}
		case ANIMATIONS::FLYRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(138, 387, 156, 405, d3dtex), 600);
			ani->Add(new Sprite(158, 387, 176, 405, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(98, 387, 116, 405, d3dtex), 600);
			ani->Add(new Sprite(78, 387, 96, 405, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}
	FLYRight();
}
void Orbs::Update(DWORD dt)
{

	Physical(dt);

	if (wPosition->x > 1520) {
		FLYLeft();
	}
	if (wPosition->x < 1359)
	{
		FLYRight();
	}

	if (animations != NULL)
		animations->Update(dt);
}
void Orbs::Physical(DWORD dt)
{

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Orbs::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Orbs::FLYLeft()
{
	this->status = Orbs::ANIMATIONS::FLYLEFT;
	this->SetVelocity(D3DXVECTOR2(-0.07, 0.00));
	this->animations->Start(ANIMATIONS::FLYLEFT);
}
void Orbs::FLYRight()
{
	this->status = Orbs::ANIMATIONS::FLYRIGHT;
	this->SetVelocity(D3DXVECTOR2(0.07, 0.00));
	this->animations->Start(ANIMATIONS::FLYRIGHT);

}