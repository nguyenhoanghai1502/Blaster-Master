#include "Sprite.h"
#include "Global.h"


Sprite::Sprite(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture)
{
	this->border.left = left;
	this->border.right = right;
	this->border.top = top;
	this->border.bottom = bottom;
	this->texture = texture;
	size.x = right - left + 1;
	size.y = bottom - top + 1;
}

RECT Sprite::Border()
{
	return border;
}

D3DXVECTOR2 Sprite::Size()
{
	return size;
}

void Sprite::Draw(D3DXVECTOR2 position, float opacity)
{
	D3DXVECTOR3 p(Global::GetInstance()->_Camera->Convert(position).x, Global::GetInstance()->_Camera->Convert(position).y, 0);
	Global::GetInstance()->_SpriteHandler->Draw(texture, &border, NULL, &p, D3DCOLOR_ARGB((int)(opacity * 255), 255, 255, 255));
}

Sprite::~Sprite()
{
}
