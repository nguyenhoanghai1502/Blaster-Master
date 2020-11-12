#include "Floaters.h"
Floaters::Floaters()
{
	this->direction = 1;
	this->isdown = 1;
}
void Floaters::Init()
{
	LPTEXTURE tex = new Texture(L"textures/Enemies.png", D3DCOLOR_XRGB(0, 38, 255));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::RIGHT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(152, 407, 170, 422, d3dtex), 100);
			ani->Add(new Sprite(132, 406, 150, 422, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::LEFT:
		{
			Animation* ani = new Animation();
			ani->Add(new Sprite(84, 407, 102, 422, d3dtex), 100);
			ani->Add(new Sprite(104, 406, 122, 422, d3dtex), 600);

			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		}
	}

	FlyDown();
}
void Floaters::Update(DWORD dt)
{

	Physical(dt);


	if (wPosition->y < 1060)
	{
		isdown = 1;
		FlyDown();
	}
	if (wPosition->y > 1182)
	{
		isdown = -1;
		FlyUp();
	}
	if (wPosition->x > 1908)
	{
		direction = -1;
		//isdown = 1;
		FlyUp();
	}
	if (wPosition->x < 1060)
	{
		direction = 1;
		//isdown = 1;
		FlyDown();
	}

	if (animations != NULL)
		animations->Update(dt);
}
void Floaters::Physical(DWORD dt)
{

	// van toc x
	this->wPosition->x += wVelocity->x * dt;

	// van toc y
	this->wPosition->y += wVelocity->y * dt;

}
void Floaters::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}
void Floaters::FlyUp()
{
	if (direction == -1 && isdown == -1)
	{
		this->status = Floaters::ANIMATIONS::LEFT;
		this->SetVelocity(D3DXVECTOR2(-0.05, -0.025));
		this->animations->Start(ANIMATIONS::LEFT);
	}
	if (direction == 1 && isdown == -1) {
		this->status = Floaters::ANIMATIONS::LEFT;
		this->SetVelocity(D3DXVECTOR2(0.05, -0.025));
		this->animations->Start(ANIMATIONS::LEFT);
	}
}

void Floaters::FlyDown()
{
	if (direction == -1 && isdown == 1) {
		this->status = Floaters::ANIMATIONS::LEFT;
		this->SetVelocity(D3DXVECTOR2(-0.05, 0.025));
		this->animations->Start(ANIMATIONS::LEFT);
	}
	if (direction == 1 && isdown == 1) {
		this->status = Floaters::ANIMATIONS::LEFT;
		this->SetVelocity(D3DXVECTOR2(0.05, 0.025));
		this->animations->Start(ANIMATIONS::LEFT);
	}
}
