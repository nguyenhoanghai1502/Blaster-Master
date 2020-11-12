#pragma once
#include "Jason.h"
#include"Map.h"
#include"Jumper.h"
#include"Gunner.h"
#include"Worm.h"
#include"Floaters.h"
#include"Domes.h"
#include"Insect.h"
#include"Skulls.h"
#include"Orbs.h"
using namespace std;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

class Game
{
private:

	static Game* _instance;
	vector<LPOBJECT> listObjects;
	LPMAP map;
	LPJUMPER jumper;
	LPGUNNER gunner;
	LPKEYBOARD keyboard;
	LPWORM worm;
	LPFLOATER floaters;
	LPDOMES domes;
	LPInsect insect;
	LPSkulls skulls;
	LPOrbs orbs;

public:
	static Game* GetInstance();
	void Init(HWND hWnd);
	void LoadResource();
	void Run();
	void Update(DWORD dt);
	void ProcessKeyStates();
	void Render();
	void End();
	void SwichControl();
	~Game();
};

