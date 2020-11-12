#include "Map.h"

GameMap::GameMap()
{
	map = nullptr;
	tileset = nullptr;
}


void GameMap::LoadMap(char* name)
{
	this->tileset = new TileSet();
	FILE* file = NULL;

	fopen_s(&file, "textures/area2.txt", "r");
	map = new LPTILE * [128];
	for (int i = 0; i < 128; i++)
	{
		map[i] = new LPTILE[128];
	}

	fscanf_s(file, "%f", &size.x);
	fscanf_s(file, "%f", &size.y);


	int r = 0;
	while (!feof(file))
	{
		for (int c = 0; c < 128; c++)
		{
			int tilesetID;
			fscanf_s(file, "%d", &tilesetID);

			map[c][r] = new Tile();
			map[c][r]->SetBackground(tileset->get_tile(tilesetID));
		}
		r++;
	}
}

D3DXVECTOR2 GameMap::Size()
{
	return size;
}

RECT GameMap::Border()
{
	RECT b;
	b.left = 0;
	b.top = 0;
	b.right = size.x;
	b.bottom = size.y;
	return b;
}

void GameMap::Update(DWORD dt)
{
}

void GameMap::Render()
{
	LPCAMERA camera = Global::GetInstance()->_Camera;

	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;

	for (int c = top / tile_size; c < ((botton % tile_size) == 0 ? (botton / tile_size) : ((botton / tile_size) + 1)); c++)
	{

		for (int r = left / tile_size; r < ((right % tile_size) == 0 ? (right / tile_size) : ((right / tile_size) + 1)); r++)
		{
			if (c >= 0 && r >= 0 && c < 128 && r < 128)
			{
				D3DXVECTOR2 pos(r * tile_size, c * tile_size);
				LPSPRITE TL = map[r][c]->GetBackground();
				if (TL != nullptr)
					TL->Draw(pos);

				map[r][c]->Render();
			}
		}
	}

}
