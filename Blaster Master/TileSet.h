#pragma once
#include "Object.h"
#include<unordered_map>

using namespace std;

#define tile_size 16
#define tileset_wight 218
#define titeset_hight 258



class Tile {
private:
	LPSPRITE bg;
public:
	Tile();
	void SetBackground(LPSPRITE SP);
	void Render();
	LPSPRITE GetBackground();
};
typedef Tile* LPTILE;


class TileSet
{
private:
	unordered_map<int, LPSPRITE> tileset;
	int row, colum;
public:
	TileSet();
	LPSPRITE get_tile(int id);
};




