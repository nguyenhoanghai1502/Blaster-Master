#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <vector>
#include "Camera.h"


class Global {
private:
	static Global* _instance;

public:
	HWND _HWND;								// Window handle
	LPDIRECT3DDEVICE9 _D3DDV;					// Direct3D device object
	LPDIRECT3DSURFACE9 _BackBuffer;
	LPD3DXSPRITE _SpriteHandler;			// Sprite helper library to help us draw 2D image on the screen 
	
	LPCAMERA _Camera;
	LPKEYBOARD _Keyboard;

	static double _FPS;
	static double _G;
	static double _FRICTION;

	static Global* GetInstance();							// Window handle
};