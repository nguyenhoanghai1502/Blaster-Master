#include "Gunner.h"
Gunner::Gunner()
{
	this->direction = 1;
	this->isWalking = false;
}
void Gunner::Init()
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
			ani->Add(new Sprite(132, 49, 158, 75, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(96, 49, 122, 75, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 49, 158, 75, d3dtex), 500);
			ani->Add(new Sprite(161, 50, 187, 75, d3dtex), 500);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(96, 49, 122, 75, d3dtex), 500);
			ani->Add(new Sprite(67, 50, 93, 75, d3dtex), 500);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	WalkRight();
}
void Gunner::Update(DWORD dt)
{

	Physical(dt);

	if (this->GetBottomPostion().y > 1160.0f) {
		wVelocity->y = 0;
		this->SetBottomPostion(D3DXVECTOR2(this->GetCenterPostion().x, 1160.0f));
	}

	if (wPosition->x > 1530) {
		WalkLeft();
	}
	if (wPosition->x < 1430)
	{
		WalkRight();
	}

	if (animations != NULL)
		animations->Update(dt);
}
void Gunner::Physical(DWORD dt)
{
	// Khi nhay len
	this->wVelocity->y += Global::_G * dt;
	this->wPosition->y += this->wVelocity->y * dt;

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Gunner::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Gunner::WalkLeft()
{
	this->status = Gunner::ANIMATIONS::WALKLEFT;
	this->SetVelocity(D3DXVECTOR2(-0.07, 0.00));
	this->direction = -1;
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKLEFT);
}
void Gunner::WalkRight()
{
	this->status = Gunner::ANIMATIONS::WALKRIGHT;
	this->SetVelocity(D3DXVECTOR2(0.07, 0.00));
	this->direction = 1;
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKRIGHT);

}
