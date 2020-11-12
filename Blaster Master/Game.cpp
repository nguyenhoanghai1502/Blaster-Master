#include "Game.h"

Game* Game::_instance = NULL;

void Game::Init(HWND hWnd)
{

	Global::GetInstance()->_FPS = 120;

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	Global::GetInstance()->_HWND = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&Global::GetInstance()->_D3DDV);

	if (Global::GetInstance()->_D3DDV == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	Global::GetInstance()->_D3DDV->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &Global::GetInstance()->_BackBuffer);


	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(Global::GetInstance()->_D3DDV, &Global::GetInstance()->_SpriteHandler);
}

void Game::LoadResource()
{
	Global::GetInstance()->_Camera = new Camera(D3DXVECTOR2(0, 0), 570, 400);

	map = new GameMap();
	map->LoadMap("textures/area2.txt");

	Global::GetInstance()->_Keyboard = new Keyboard();
	Global::GetInstance()->_Keyboard->Init(Global::GetInstance()->_HWND);

	SOPHIA::GetInstance()->Init();
	SOPHIA::GetInstance()->SetCenterPostion(D3DXVECTOR2(1077.0f, 1175.0f));

	Jason::GetInstance()->Init();
	Jason::GetInstance()->SetCenterPostion(D3DXVECTOR2(1101.0f, 1168.0f));

	Global::GetInstance()->_Camera->AnchorTo(SOPHIA::GetInstance()->GetPosition());
	Global::GetInstance()->_Camera->SetLimitedZone(map->Border());

	jumper = new Jumper();
	jumper->Init();
	jumper->SetCenterPostion(D3DXVECTOR2(1429, 1170.0f));

	gunner = new Gunner();
	gunner->Init();
	gunner->SetCenterPostion(D3DXVECTOR2(1411.0f, 1170.0f));

	worm = new Worm();
	worm->Init();
	worm->SetCenterPostion(D3DXVECTOR2(1228, 1170.0f));
	floaters = new Floaters();
	floaters->Init();
	floaters->SetCenterPostion(D3DXVECTOR2(1170,1050));

	domes = new Domes();
	domes->Init();
	domes->SetCenterPostion(D3DXVECTOR2(1800, 1170));

	insect = new Insect();
	insect->Init();
	insect->SetCenterPostion(D3DXVECTOR2(1800, 1113));

	skulls = new Skulls();
	skulls->Init();
	skulls->SetCenterPostion(D3DXVECTOR2(1700, 1116));

	orbs = new Orbs();
	orbs->Init();
	orbs->SetCenterPostion(D3DXVECTOR2(1417, 1104));

}

void Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / 120;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}
}

void Game::Update(DWORD dt)
{
	
	Global::GetInstance()->_Camera->Update(dt);
	Global::GetInstance()->_Keyboard->RecordKeyStates(dt);

	SOPHIA::GetInstance()->Update(dt);
	Jason::GetInstance()->Update(dt);
	jumper->Update(dt);

	gunner->Update(dt);

	worm->Update(dt);

	floaters->Update(dt);
	domes->Update(dt);
	insect->Update(dt);
	skulls->Update(dt);
	orbs->Update(dt);
	ProcessKeyStates();

}

void Game::ProcessKeyStates()
{
	LPKEYBOARD keyboard = Global::GetInstance()->_Keyboard;

	bool keyLeft = keyboard->IsKeyDown(DIK_LEFT);
	bool pressLeft = keyboard->IsKeyPress(DIK_LEFT);
	bool keyRight = keyboard->IsKeyDown(DIK_RIGHT);
	bool pressRight = keyboard->IsKeyPress(DIK_RIGHT);
	bool keyUp = keyboard->IsKeyDown(DIK_UP);
	bool keyDown = keyboard->IsKeyDown(DIK_DOWN);
	bool keyC = keyboard->IsKeyPress(DIK_C);
	bool keyZ = keyboard->IsKeyPress(DIK_Z);
	bool keyX = keyboard->IsKeyPress(DIK_X);
	bool keyShift = (keyboard->IsKeyPress(DIK_RSHIFT) || keyboard->IsKeyPress(DIK_LSHIFT));

	if (keyShift) {
		SwichControl();
	}
}

void Game::Render()
{

	if (Global::GetInstance()->_D3DDV->BeginScene())
	{
		Global::GetInstance()->_D3DDV->ColorFill((Global::GetInstance()->_BackBuffer), NULL, BACKGROUND_COLOR);
		Global::GetInstance()->_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		map->Render();

		SOPHIA::GetInstance()->Render();

		Jason::GetInstance()->Render();
		floaters->Render();
		worm->Render();
		jumper->Render();
		gunner->Render();
		domes->Render();
		insect->Render();
		skulls->Render();
		orbs->Render();
		Global::GetInstance()->_SpriteHandler->End();
		Global::GetInstance()->_D3DDV->EndScene();
	}
	(Global::GetInstance()->_D3DDV)->Present(NULL, NULL, NULL, NULL);
}

void Game::End()
{
}

void Game::SwichControl()
{
	LPSOPHIA sophia = SOPHIA::GetInstance();
	LPJASON jason = Jason::GetInstance();

	if (sophia->GetIsControlling() == true && jason->GetIsControlling() == false) {
		if ((sophia->GetStatus()==SOPHIA::ANIMATIONS::IDLELEFT) || (sophia->GetStatus() == SOPHIA::ANIMATIONS::IDLERIGHT))
		{
			sophia->SetIsControlling(false);
			//DebugOut(L"opendoor\n");
			//sophia->OpenDoor();
			jason->SetIsControlling(true);
		}
	}
	else
	if (jason->GetIsControlling() == true && sophia->GetIsControlling() == false) {
		if ((jason->GetStatus()==Jason::ANIMATIONS::IDLERIGHT || jason->GetStatus() == Jason::ANIMATIONS::IDLELEFT))
		{
			jason->SetIsControlling(false);
			sophia->SetIsControlling(true);
		}
	}
	//if xe: is + ng:no
	//		if() ! // cac truong hop k chuyen dc cua xe
	//			xe->no; xe->mocua;
	//			ng->is
	//
	//if ng: is + xe:no
	//		if() ! // cac truong hop k chuyen dc cua ng
	//			ng->no; ng->nhay vo xe;
	//			ng->is
	//
}

Game* Game::GetInstance()
{
	if (_instance == NULL) _instance = new Game();
	return _instance;
}

Game::~Game()
{
	if (Global::GetInstance()->_SpriteHandler != NULL) Global::GetInstance()->_SpriteHandler->Release();
	if (Global::GetInstance()->_BackBuffer != NULL) Global::GetInstance()->_BackBuffer->Release();
	if (Global::GetInstance()->_D3DDV != NULL) Global::GetInstance()->_D3DDV->Release();
}



