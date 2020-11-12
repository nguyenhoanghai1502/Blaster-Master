#include "Jumper.h"
Jumper::Jumper()
{
	this->direction = 1;
	this->isWalking = false;
}
void Jumper::Init()
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
			ani->Add(new Sprite(152, 499, 167, 525, d3dtex), 500);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(87, 499, 102, 525, d3dtex), 500);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKRIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(132, 500, 149, 525, d3dtex), 500);
			ani->Add(new Sprite(152, 499, 167, 525, d3dtex), 500);
			ani->Add(new Sprite(170, 500, 185, 525, d3dtex), 500);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKLEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(105, 500, 122, 525, d3dtex), 500);
			ani->Add(new Sprite(87, 499, 102, 525, d3dtex), 500);
			ani->Add(new Sprite(69, 500, 84, 525, d3dtex), 500);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	WalkRight();
}
void Jumper::Update(DWORD dt)
{

	Physical(dt);

	if (this->GetBottomPostion().y > 1160.0f) {
		wVelocity->y = 0;
		this->SetBottomPostion(D3DXVECTOR2(this->GetCenterPostion().x, 1160.0f));
	}

	if (wPosition->x > 1530) {
		WalkLeft();
	}
	if (wPosition->x < 1410)
	{
		WalkRight();

	}
	if (wPosition->x == 1340 || wPosition->x == 1406)
	{
		wPosition->y = 1250;
	}
	if (animations != NULL)
		animations->Update(dt);
}
void Jumper::Physical(DWORD dt)
{
	// Khi nhay len
	this->wVelocity->y += Global::_G * dt;
	this->wPosition->y += this->wVelocity->y * dt;

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Jumper::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Jumper::WalkLeft()
{
	this->status = Jumper::ANIMATIONS::WALKLEFT;
	this->SetVelocity(D3DXVECTOR2(-0.07, 0.00));
	this->direction = -1;
	this->isWalking = true;
	this->animations->Start(ANIMATIONS::WALKLEFT);
}
void Jumper::WalkRight()
{
	this->status = Jumper::ANIMATIONS::WALKRIGHT;
	this->SetVelocity(D3DXVECTOR2(0.07, 0.00));
	this->direction = 1;
	this->animations->Start(ANIMATIONS::WALKRIGHT);

}
void Jumper::Jump() {
	if (wVelocity->y == 0) {

		this->SetVelocity(D3DXVECTOR2(0, -0.3));
	}
	else {
		return;
	}
}
