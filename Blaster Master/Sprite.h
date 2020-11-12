#pragma once

#include "Texture.h"

class Sprite
{
private:
	LPDIRECT3DTEXTURE9 texture;
	RECT border;
	D3DXVECTOR2 size;
public:
	Sprite(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 gettexture() { return texture; }
	RECT Border();
	D3DXVECTOR2 Size();
	void Draw(D3DXVECTOR2 position, float opacity = 1.0f);
	~Sprite();
};

typedef Sprite* LPSPRITE;

