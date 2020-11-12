#include "Worm.h"
Worm::Worm()
{
	this->direction = 1;
	this->isWalking = false;
}
void Worm::Init()
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
			ani->Add(new Sprite(172, 412, 190, 422, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(64, 412, 82, 422, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(172, 412, 190, 422, d3dtex), 600);
			ani->Add(new Sprite(191, 412, 209, 422, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(64, 412, 82, 422, d3dtex), 600);
			ani->Add(new Sprite(46, 412, 64, 422, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	WalkRight();
}
void Worm::Update(DWORD dt)
{

	Physical(dt);

	if (this->GetBottomPostion().y > 1175.0f) {
		wVelocity->y = 0;
		this->SetBottomPostion(D3DXVECTOR2(this->GetCenterPostion().x, 1175.0f));
	}

	if (wPosition->x > 1339) {
		WalkLeft();
	}
	if (wPosition->x < 1100.0f)
	{
		WalkRight();
	}

	if (animations != NULL)
		animations->Update(dt);
}
void Worm::Physical(DWORD dt)
{
	// Khi nhay len
	this->wVelocity->y += Global::_G * dt;
	this->wPosition->y += this->wVelocity->y * dt;

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Worm::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Worm::WalkLeft()
{
	this->status = Worm::ANIMATIONS::WALKLEFT;
	this->SetVelocity(D3DXVECTOR2(-0.07, 0.00));
	this->direction = -1;
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKLEFT);
}
void Worm::WalkRight()
{
	this->status = Worm::ANIMATIONS::WALKRIGHT;
	this->SetVelocity(D3DXVECTOR2(0.07, 0.00));
	this->direction = 1;
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKRIGHT);

}