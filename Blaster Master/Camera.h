#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Debug.h"
#include "Keyboard.h"

class Camera
{
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;  //w,h của camera
	D3DXVECTOR2* anchorPoint; //Điểm neo camera theo 1 vật
	RECT* limitedZone; //Vùng giới hạn

public:
	Camera(D3DXVECTOR2 pos, float width, float height);
	D3DXVECTOR2 Position();
	D3DXVECTOR2 Center(); //Điểm trung tâm camera
	D3DXVECTOR2 Size();
	RECT Border(); //Viền
	void SetPosition(D3DXVECTOR2 pos);
	void SetCenter(D3DXVECTOR2 cen);
	void SetLimitedZone(RECT zone);
	void AnchorTo(D3DXVECTOR2* point);
	void Free();
	void Update(DWORD dt);
	//void ProcessKeyStates(LPKEYBOARD keyboard);
	D3DXVECTOR2 Convert(D3DXVECTOR2 pos); //convert từ world sang viewport
	~Camera();
};

typedef Camera* LPCAMERA;
