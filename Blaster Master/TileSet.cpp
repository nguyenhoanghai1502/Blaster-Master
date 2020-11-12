#include "TileSet.h"



TileSet::TileSet()
{
	//new text ture 
	LPCWSTR path = L"textures/Area2TileSet.png";
	Texture *texture = new Texture(path, D3DCOLOR_XRGB(0, 0, 0));
	this->row = (titeset_hight+2) / (tile_size + 4);
	this->colum = (tileset_wight+2) / (tile_size + 4);
	int index = 1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < colum; j++)
		{
			int left = j* (tile_size+4)+1;
			int top = i* (tile_size+4)+1;
			int right = left + tile_size;
			int bottom = top + tile_size;
			LPSPRITE tile = new Sprite(left, top, right, bottom, texture->LPDIRECT3DTEXTURE());
			tileset[index] = tile;
			index++;
		}
	}
}

LPSPRITE TileSet::get_tile(int id)
{
	if (tileset.size() > 0 && id > 0)
		return tileset.at(id);
	else
	{
		return nullptr;
	}
}

Tile::Tile()
{
	this->bg = nullptr;
}


void Tile::SetBackground(LPSPRITE SP)
{
	bg = SP;
}

void Tile::Render()
{
}

LPSPRITE Tile::GetBackground()
{
	return bg;
}

