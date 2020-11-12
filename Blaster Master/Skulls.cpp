#include "Skulls.h"
Skulls::Skulls()
{
	this->direction = 1;
	this->isWalking = false;
}
void Skulls::Init()
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
			ani->Add(new Sprite(192, 529, 212, 549, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(41, 530, 59, 549, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(192, 529, 212, 549, d3dtex), 600);
			ani->Add(new Sprite(172, 528, 191, 549, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::FLYLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(41, 530, 59, 549, d3dtex), 600);
			ani->Add(new Sprite(61, 529, 80, 549, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}
	FLYRight();
}
void Skulls::Update(DWORD dt)
{

	Physical(dt);

	if (wPosition->x > 1905) {
		FLYLeft();
	}
	if (wPosition->x < 1679)
	{
		FLYRight();
	}

	if (animations != NULL)
		animations->Update(dt);
}
void Skulls::Physical(DWORD dt)
{
	// Khi nhay len

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Skulls::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Skulls::FLYLeft()
{
	this->status = Skulls::ANIMATIONS::FLYLEFT;
	this->SetVelocity(D3DXVECTOR2(-0.10, 0.00));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::FLYLEFT);
}
void Skulls::FLYRight()
{
	this->status = Skulls::ANIMATIONS::FLYRIGHT;
	this->SetVelocity(D3DXVECTOR2(0.10, 0.00));
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::FLYRIGHT);

}