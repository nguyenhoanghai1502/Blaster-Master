#include<fstream>
#include<iostream>
#include"TileSet.h"

#define Tile_Size 16
#define Max_Map_x 128
#define Max_Map_y 128

using namespace std;
class GameMap
{
private:
	LPTILE** map;
	TileSet* tileset;
	D3DXVECTOR2 size;

public:
	GameMap();
	void LoadMap(char* path);
	D3DXVECTOR2 Size();
	RECT Border();
	void Update(DWORD dt);
	void Render();
};
typedef GameMap* LPMAP;
