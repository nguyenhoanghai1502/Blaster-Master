#include "SOPHIA.h"

SOPHIA* SOPHIA::_instance = new SOPHIA();

SOPHIA::SOPHIA()
{
	this->direction = 1;
	this->maxVelocity = D3DXVECTOR2(0.1, 1);
	this->isWalking = false;
	this->isControlling = true;
}

void SOPHIA::Init()
{
	wheelL = new WheelLeft();
	wheelL->Init();
	wheelR = new WheelRight();
	wheelR->Init();
	body = new Body();
	body->Init();
	head = new Head();
	head->Init(body);
	gun = new Gun();
	gun->Init(body);

	IdleRight();
}

void SOPHIA::Update(DWORD dt)
{
	//DebugOut(L"S: %d\n", SOPHIA::GetInstance()->GetStatus());
	this->ProcessKeyStates();

	Physical(dt);

	if (wVelocity->x == 0) {
		Stop();
	}

	if (this->GetBottomPostion().y > 1175.0f) {
		wVelocity->y = 0;
		this->SetBottomPostion(D3DXVECTOR2(this->GetCenterPostion().x, 1175.0f));
	
	}
	wheelL->Update(dt);
	wheelR->Update(dt);
	body->Update(dt);
	head->Update(dt);
	gun->Update(dt);
}

void SOPHIA::Physical(DWORD dt)
{
	// neu vat ngung di chuyen -> luc ma sat = 0
	if (wVelocity->x == 0) {
		friction = 0;
	}
	// neu vat di chuyen -> luc ma sat nguoc huong voi huong di chuyen
	if (wVelocity->x != 0) {
		friction = (-direction) * Global::_FRICTION;
	}

	// Khi nhay len
	this->wVelocity->y += Global::_G * dt;
	this->wPosition->y += this->wVelocity->y * dt;



	//DebugOut(L"ms: %f - Dir: %d  - A: %f\n", friction, direction, wAcceleration->x);

	/// cap nhat van toc theo gia toc
	// van toc x
	this->wVelocity->x += (wAcceleration->x + friction) * dt;
	//van toc y
	this->wVelocity->y += wAcceleration->y * dt;

	/// gioi han van toc
	this->wVelocity->x = (abs(wVelocity->x) <= maxVelocity.x) ? wVelocity->x : (direction)*maxVelocity.x;
	this->wVelocity->y = (abs(wVelocity->y) <= maxVelocity.y) ? wVelocity->y : (direction)*maxVelocity.y;

	/// cap nhat toa do theo van toc
	this->wPosition->x += this->wVelocity->x * dt;
	this->wPosition->y += this->wVelocity->y * dt;

	/// gioi han van toc bang 0 khi giam toc
	if (wVelocity->x < 0 && direction == 1)
		this->wVelocity->x = 0;
	if (wVelocity->x > 0 && direction == -1)
		this->wVelocity->x = 0;
}

void SOPHIA::Render()
{
	wheelL->Render();
	wheelR->Render();
	body->Render();
	head->Render();
	gun->Render();
}

void SOPHIA::ProcessKeyStates()
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
	

	if (isControlling) {
		if (keyRight) {
			this->WalkRight();
		}
		else
		if (keyLeft)
		{
			this->WalkLeft();
		}
		else
		{
			this->wAcceleration->x = 0;
		}

		if (keyUp) {
			this->Up();
		}

		if(keyDown)
		{
			this->Down();
		}
		

		

		if (keyX) {
			this->Jump();
		}
	}
}

SOPHIA* SOPHIA::GetInstance()
{
	if (_instance == NULL) _instance = new SOPHIA();
	return _instance;
}

D3DXVECTOR2 SOPHIA::GetMaxVelocity()
{
	return this->maxVelocity;
}

bool SOPHIA::IsAni(int aniid)
{
	if (animations != nullptr) {
		if (this->GetStatus() == aniid)
			return true;
	}
	return false;
}

int SOPHIA::GetDirection()
{
	return this->direction;
}

bool SOPHIA::GetIsControlling()
{
	return this->isControlling;
}

void SOPHIA::SetIsControlling(bool _isControlling)
{
	this->isControlling = _isControlling;
}

void SOPHIA::Stop()
{
	if (isWalking) {
		isWalking = false;
		if (status == ANIMATIONS::WALKRIGHT) {
			status = ANIMATIONS::IDLERIGHT;
		}
		else
		if (status == ANIMATIONS::WALKLEFT) {
			status = ANIMATIONS::IDLELEFT;
		}

		this->wheelR->Idle();
		this->wheelL->Idle();
		this->body->SetUndulate(false);
	}
}

void SOPHIA::IdleRight()
{
	this->status = SOPHIA::ANIMATIONS::IDLERIGHT;
	this->direction = 1;

	this->wheelR->Idle();
	this->wheelL->Idle();
	this->body->SetUndulate(false);
}

void SOPHIA::IdleLeft()
{
	this->status = SOPHIA::ANIMATIONS::IDLELEFT;
	this->direction = -1;

	this->wheelR->Idle();
	this->wheelL->Idle();
	this->body->SetUndulate(false);
}

void SOPHIA::WalkLeft()
{
	this->status = SOPHIA::ANIMATIONS::WALKLEFT;
	this->SetAcceleration(D3DXVECTOR2(-0.0008, 0.00));
	this->direction = -1;
	this->isWalking = true;

	this->wheelR->SpinLeft();
	this->wheelL->SpinLeft();
	this->body->SetUndulate(true);
}

void SOPHIA::WalkRight()
{
	this->status = SOPHIA::ANIMATIONS::WALKRIGHT;
	this->SetAcceleration(D3DXVECTOR2(0.0008, 0.00));
	this->direction = 1;
	this->isWalking = true;

	this->wheelR->SpinRight();
	this->wheelL->SpinRight();
	this->body->SetUndulate(true);
}

void SOPHIA::Up()
{
	if (status != STATUS::UP) {
		this->status = STATUS::UP;
		this->wheelL->Shrink();
		this->wheelR->Shrink();
		if (this->direction == 1) {
			this->gun->UpRight();
			this->body->UpRight();
			this->head->UpRight();
		}
		else {
			this->gun->UpLeft();
			this->body->UpLeft();
			this->head->UpLeft();
		}
	}
}


void SOPHIA::Jump()
{
	if (wVelocity->y == 0) {
		this->SetVelocity(D3DXVECTOR2(0, -0.3));
	}
	else {
		return;
	}
}

void SOPHIA::OpenDoor()
{
	if (this->direction == 1) {
		this->head->OpenDoorRight();
	}
	else {
		this->head->OpenDoorLeft();
	}	
}

void SOPHIA::Down()
{
	if (status != STATUS::UPTOIDLE) {
		this->status = STATUS::UPTOIDLE;
		this->wheelL->Indent();
		this->wheelR->Indent();

		if (direction == 1) {
			this->body->DownRight();
			this->head->DownRight();
			this->gun->DownRight();
		}
		else {
			this->body->DownLeft();
			this->head->DownLeft();
			this->gun->DownLeft();
		}
	}
	
}




/// <summary>
/// =============================== WheelLeft ===========================================
/// </summary>

WheelLeft::WheelLeft()
{
	this->activities = new Activities();
	this->move = new D3DXVECTOR2(9, -1);
}

void WheelLeft::Init()
{
	LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	Animation* ani = new Animation();
	ani->Add(new Sprite(3, 21, 11, 29, d3dtex), 100);
	ani->Add(new Sprite(12, 21, 20, 29, d3dtex), 100);
	ani->Add(new Sprite(21, 21, 29, 29, d3dtex), 100);
	ani->Add(new Sprite(30, 21, 38, 29, d3dtex), 100);
	this->animations->Add(ani);
	ani->Repeat(true);
	this->animations->Start(ANIMATIONS::SPIN);

	//--------------- da tao xong animation -----------------------------
	LPACTIVITY act_shrink = new Activity(ani, this);
	act_shrink->Add(D3DXVECTOR2(-1, -1), 100);
	act_shrink->Add(D3DXVECTOR2(-1, -1), 100);
	this->activities->Add(act_shrink); // shrink

}

void WheelLeft::Update(DWORD dt)
{
	this->SetCenterPostion(SOPHIA::GetInstance()->GetCenterPostion() - *move);

	if (animations != NULL)
		animations->Update(dt);

	if (activities != NULL) {
		activities->Update(dt);
	}
}

void WheelLeft::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}

void WheelLeft::Idle()
{
	if (animations != nullptr) {
		animations->Pause();
	}
}

void WheelLeft::SpinRight()
{
	if (animations != nullptr) {
		animations->Resume(1);
	}
}

void WheelLeft::SpinLeft()
{
	if (animations != nullptr) {
		animations->Resume(-1);
	}
}

void WheelLeft::Shrink()
{
	if (activities != nullptr) {
		this->activities->Start(ACTIVITIES::SHRINK);
	}
}

void WheelLeft::Indent()
{
	if (activities != nullptr) {
		this->activities->Resume(-1);
	}
}


WheelLeft::~WheelLeft()
{
}








/// <summary>
/// =============================== WheelRight ===========================================
/// </summary>
/// 
WheelRight::WheelRight()
{
	this->activities = new Activities();
	this->move = new D3DXVECTOR2(7, 1);
}

void WheelRight::Init()
{
	LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	Animation* ani = new Animation();
	ani->Add(new Sprite(12, 21, 20, 29, d3dtex), 100);
	ani->Add(new Sprite(21, 21, 29, 29, d3dtex), 100);
	ani->Add(new Sprite(30, 21, 38, 29, d3dtex), 100);
	ani->Add(new Sprite(3, 21, 11, 29, d3dtex), 100);
	this->animations->Add(ani);
	ani->Repeat(true);
	this->animations->Start(ANIMATIONS::SPIN);

	//--------------- da tao xong animation -----------------------------

	LPACTIVITY act_shrink = new Activity(ani,this);
	act_shrink->Add(D3DXVECTOR2(-1, 1), 100);
	act_shrink->Add(D3DXVECTOR2(-1, 1), 100);
	this->activities->Add(act_shrink); // shrink

}

void WheelRight::Update(DWORD dt)
{
	//DebugOut(L"move: %f\n", move->x);

	//this->UpdateSpeedRotate(abs(this->wVelocity->x / SOPHIA::GetInstance()->GetMaxVelocity().x));

	this->SetCenterPostion(SOPHIA::GetInstance()->GetCenterPostion() + *move);

	//DebugOut(L"W: %d\n", SOPHIA::GetInstance()->GetStatus());

	if (animations != NULL) {
		animations->Update(dt);
	}

	if (activities != nullptr) {
		activities->Update(dt);
	}

}

void WheelRight::UpdateSpeedRotate(double speed)
{
	this->animations->GetCurrentAnimation()->UpdateSpeed(speed);
}


void WheelRight::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}

void WheelRight::Idle()
{
	if (animations != nullptr) {
		animations->Pause();
	}
}

void WheelRight::SpinRight()
{
	if (animations != nullptr) {
		animations->Resume(1);
	}

}

void WheelRight::SpinLeft()
{
	if (animations != nullptr) {
		animations->Resume(-1);
	}
}

void WheelRight::Shrink()
{
	if (activities != nullptr) {
		this->activities->Start(ACTIVITIES::SHRINK);
	}
}

void WheelRight::Indent()
{
	if (activities != nullptr) {
		this->activities->Resume(-1);
	}
}


WheelRight::~WheelRight()
{
}



/// <summary>
/// =============================== Body ===========================================
/// </summary>
/// 



Body::Body()
{
	a = 0;
	move = new D3DXVECTOR2(0, 0);
	isUndulating = false;
	this->activities = new Activities();
}

void Body::Init()
{
	//texture trái
	LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();
	//texture phải
	LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT: {
			//Ngang phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(400, 12, 406, 19, d3dtexR), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
			}
		case ANIMATIONS::IDLELEFT: {
			// Ngang trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(4, 12, 10, 19, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
			}			
		}
	}

	////Ngang trái
	//Animation* ani_body_horizon = new Animation();
	//ani_body_horizon->Add(new Sprite(4, 12, 10, 19, d3dtex), 1000);

	////Ngang phải
	//Animation* ani_body_horizonR = new Animation();
	//ani_body_horizonR->Add(new Sprite(400, 12, 406, 19, d3dtexR), 1000);

	////Dọc trái
	//Animation* ani_body_verticalL = new Animation();
	//ani_body_verticalL->Add(new Sprite(13, 13, 20, 19, d3dtex), 1000);

	////Dọc phải
	//Animation* ani_body_verticalR = new Animation();
	//ani_body_verticalR->Add(new Sprite(390, 13, 397, 19, d3dtexR), 1000);

	////Chéo lên trái
	//Animation* ani_body_crossL = new Animation();
	//ani_body_crossL->Add(new Sprite(21, 12, 29, 20, d3dtex), 1000);

	////Chéo xuống trái 
	//Animation* ani_body_crossL_down = new Animation();
	//ani_body_crossL_down->Add(new Sprite(30, 12, 38, 20, d3dtex), 1000);

	////Chéo lên phải
	//Animation* ani_body_crossR_up = new Animation();
	//ani_body_crossR_up->Add(new Sprite(381, 12, 389, 20, d3dtexR), 1000);

	////Chéo xuống phải 
	//Animation* ani_body_crossR_down = new Animation();
	//ani_body_crossR_down->Add(new Sprite(372, 12, 380, 20, d3dtexR), 1000);

	//--------------- da tao xong animation -----------------------------
	//upright
	LPACTIVITY act_up_right = new Activity(this->animations->GetAnimation(ANIMATIONS::IDLERIGHT), this);
	act_up_right->Add(D3DXVECTOR2(0, 0), 100);
	act_up_right->Add(D3DXVECTOR2(0, -2), 100);
	act_up_right->Add(D3DXVECTOR2(0, -2), 100);
	this->activities->Add(act_up_right);

	//upleft
	LPACTIVITY act_up_left = new Activity(this->animations->GetAnimation(ANIMATIONS::IDLELEFT), this);
	act_up_left->Add(D3DXVECTOR2(0, 0), 100);
	act_up_left->Add(D3DXVECTOR2(0, -2), 100);
	act_up_right->Add(D3DXVECTOR2(0, -2), 100);
	this->activities->Add(act_up_left);
}

void Body::Update(DWORD dt)
{

	Physical(dt);	

	this->SetCenterPostion(SOPHIA::GetInstance()->GetCenterPostion() + *move);

	if (SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::IDLERIGHT || SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::WALKRIGHT ) {
		this->IdleRight();
	}
	else
	if (SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::IDLELEFT || SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::WALKLEFT) {
		this->IdleLeft();
	}

	if (animations != NULL)
		animations->Update(dt);

	if (activities != nullptr) {
		activities->Update(dt);
	}
}

void Body::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}


void Body::IdleRight()
{
	this->animations->Start(ANIMATIONS::IDLERIGHT);
}

void Body::IdleLeft()
{
	this->animations->Start(ANIMATIONS::IDLELEFT);
}

void Body::UpRight()
{
	this->activities->Start(ACTIVITIES::UP_RIGHT);
}

void Body::UpLeft()
{
	this->activities->Start(ACTIVITIES::UP_LEFT);
}

void Body::DownRight()
{
	this->activities->Resume(-1);
}

void Body::DownLeft()
{
	this->activities->Resume(-1);
}

void Body::SetUndulate(bool isUndulating)
{
	this->isUndulating = isUndulating;
}

void Body::Physical(DWORD dt)
{
	t += dt * 3.14 / 100;
	
	if (isUndulating) {
		move->y = (sin(t) * 0.75);
	}
	else
	{
		move->y = 0;
	}
	
}


Body::~Body()
{
}




/// <summary>
/// =============================== Head ===========================================
/// </summary>
/// 



Head::Head()
{
	this->move = new D3DXVECTOR2(9, 8);
	this->activities = new Activities();
}

void Head::Init(LPBODY body)
{
	this->body = body;
	//texture trái
	LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	//texture phải
	LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT: {
			//Ngang phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT: {
			// Ngang trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(39, 3, 55, 11, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::ROTATERIGHT: {
			// Xoay từ trái sang phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(39, 3, 55, 11, d3dtex), 100);
			ani->Add(new Sprite(56, 3, 72, 11, d3dtex), 100);
			ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), 100);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::ROTATELEFT: {
			// Xoay từ phải sang trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), 100);
			ani->Add(new Sprite(338, 3, 354, 11, d3dtexR), 100);
			ani->Add(new Sprite(39, 3, 55, 11, d3dtex), 100);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::UPRIGHT: {
			// Up phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), 1000);
			ani->Add(new Sprite(321, 4, 337, 19, d3dtexR), 1000);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::UPLEFT: {
			// Up trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(39, 3, 55, 11, d3dtex), 1000);
			ani->Add(new Sprite(73, 4, 89, 19, d3dtex), 1000);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::OPENDOORRIGHT: {
			// Mở cửa bên phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(252, 3, 268, 19, d3dtexR), 1000);
			ani->Add(new Sprite(269, 3, 285, 19, d3dtexR), 1000);
			ani->Add(new Sprite(355, 3, 371, 11, d3dtexR), 1000);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::OPENDOORLEFT: {
			// Mở cửa bên phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(142, 3, 158, 19, d3dtex), 1000);
			ani->Add(new Sprite(125, 3, 141, 19, d3dtex), 1000);
			ani->Add(new Sprite(39, 3, 55, 11, d3dtex), 1000);
			this->animations->Add(ani);
			break;
		}
		}
	}


	////Ngang-Trái
	//Animation* ani_left_head = new Animation();
	//ani_left_head->Add(new Sprite(39, 3, 55, 11, d3dtex), 1000);

	////Ngang-Phải
	//Animation* ani_right_head = new Animation();
	//ani_right_head->Add(new Sprite(355, 3, 371, 11, d3dtexR), 1000);

	////Chéo lên-Trái
	//Animation* ani_left_crossUp_head = new Animation();
	//ani_left_crossUp_head->Add(new Sprite(73, 4, 89, 19, d3dtex), 1000);

	////Chéo lên-Phải
	//Animation* ani_right_crossUp_head = new Animation();
	//ani_right_crossUp_head->Add(new Sprite(321, 4, 337, 19, d3dtexR), 1000);

	////Dọc -Trái
	//Animation* ani_left_vertical_head = new Animation();
	//ani_left_vertical_head->Add(new Sprite(90, 3, 98, 19, d3dtex), 1000);

	////Dọc -Phải
	//Animation* ani_right_vertical_head = new Animation();
	//ani_right_vertical_head->Add(new Sprite(312, 3, 320, 19, d3dtexR), 1000);

	////Chéo xuống - Trái
	//Animation* ani_left_crossDown_head = new Animation();
	//ani_left_crossDown_head->Add(new Sprite(109, 3, 124, 19, d3dtex), 1000);

	////Chéo xuống - Phải
	//Animation* ani_right_crossDown_head = new Animation();
	//ani_right_crossDown_head->Add(new Sprite(286, 3, 302, 19, d3dtexR), 1000);
	//

	//--------------- da tao xong animation -----------------------------
	//upright
	LPACTIVITY act_up_right = new Activity(this->animations->GetAnimation(ANIMATIONS::UPRIGHT), this);
	act_up_right->Add(D3DXVECTOR2(-4, -1), 1000);
	this->activities->Add(act_up_right);

	//upleft
	LPACTIVITY act_up_left = new Activity(this->animations->GetAnimation(ANIMATIONS::UPLEFT), this);
	act_up_left->Add(D3DXVECTOR2(0, 0), 100);
	act_up_left->Add(D3DXVECTOR2(1, -2), 100);
	act_up_left->Add(D3DXVECTOR2(1, -2), 100);
	this->activities->Add(act_up_left);

}

void Head::Update(DWORD dt)
{
	//DebugOut(L"Head Animation: %d\n", animations->GetCurrentAnimationID());
	this->SetCenterPostion(body->GetCenterPostion() - *move);

	if (SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::IDLERIGHT || SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::WALKRIGHT) {
		this->IdleRight();
	}
	else
	if (SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::IDLELEFT || SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::WALKLEFT) {
		this->IdleLeft();
		this->SetCenterPostion(body->GetCenterPostion() - *move + *(new D3DXVECTOR2(8, 0)));
	}
	if (animations != NULL)
		animations->Update(dt);

	if (activities != nullptr) {
		activities->Update(dt);
	}
}

void Head::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);

}

void Head::IdleRight()
{
	this->animations->Start(ANIMATIONS::IDLERIGHT);
}

void Head::IdleLeft()
{
	this->animations->Start(ANIMATIONS::IDLELEFT);
}

void Head::RotateRight()
{
	this->animations->Start(ANIMATIONS::ROTATERIGHT);
}

void Head::RotateLeft()
{
	this->animations->Start(ANIMATIONS::ROTATELEFT);
}

void Head::UpRight()
{
	//DebugOut(L"Head UP out\n");
	if (status != STATUS::UP) {
		//DebugOut(L"Head UP in\n");
		status = STATUS::UP;
		this->animations->Start(ANIMATIONS::UPRIGHT);
		this->activities->Start(ACTIVITIES::UP_RIGHT);
	}
}

void Head::UpLeft()
{
	this->animations->Start(ANIMATIONS::UPLEFT);
	this->activities->Start(ACTIVITIES::UP_LEFT);
}

void Head::DownRight()
{
	//DebugOut(L"Head Down out\n");
	if (status != STATUS::DOWN) {
		//DebugOut(L"Head Down in\n");
		status = STATUS::DOWN;

		this->activities->Resume(-1);
		this->animations->Resume(-1);
	}
	
}

void Head::DownLeft()
{
	this->activities->Resume(-1);
	this->animations->Resume(-1);
}

void Head::OpenDoorRight()
{
	this->animations->Restart(ANIMATIONS::OPENDOORRIGHT);
}

void Head::OpenDoorLeft()
{
	this->animations->Restart(ANIMATIONS::OPENDOORLEFT);
}

Head::~Head()
{
}


/// <summary>
/// =============================== Gun ===========================================
/// </summary>
/// 



Gun::Gun()
{
	this->move = new D3DXVECTOR2(-9, 5);
	this->activities = new Activities();
}

void Gun::Init(LPBODY body)
{
	this->body = body;

	//texture trái
	LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();

	//texture phải
	LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();

	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT: {
			//Ngang phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
			}
		case ANIMATIONS::IDLELEFT: {
			// Ngang trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(12, 5, 19, 9, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
			}
		case ANIMATIONS::UPRIGHT: {
			Animation* ani = new Animation();
			ani->Add(new Sprite(391, 5, 398, 9, d3dtexR), 100);
			ani->Add(new Sprite(381, 3, 389, 11, d3dtexR), 100);
			ani->Add(new Sprite(374, 3, 378, 10, d3dtexR), 100);
			this->animations->Add(ani);
			break;
			}
		case ANIMATIONS::UPLEFT: {
			Animation* ani = new Animation();
			ani->Add(new Sprite(12, 5, 19, 9, d3dtex), 100);
			ani->Add(new Sprite(21, 3, 29, 11, d3dtex), 100);
			ani->Add(new Sprite(32, 3, 36, 10, d3dtex), 100);
			this->animations->Add(ani);
			break;
			}
		}
	}

	////Chéo xuống - Trái
	//Animation* ani_left_crossDown_gun = new Animation();
	//ani_left_crossDown_gun->Add(new Sprite(3, 3, 11, 11, d3dtex), 1000);

	////Chéo xuống - Phải
	//Animation* ani_right_crossDown_gun = new Animation();
	//ani_right_crossDown_gun->Add(new Sprite(399, 3, 407, 11, d3dtexR), 1000);

	////Ngang - Trái 
	//Animation* ani_left_gun = new Animation();
	//ani_left_gun->Add(new Sprite(12, 5, 19, 9, d3dtex), 1000);

	////Ngang - Phải 
	//Animation* ani_right_gun = new Animation();
	//ani_right_gun->Add(new Sprite(391, 5, 398, 9, d3dtexR), 1000);

	////Chéo lên - Trái
	//Animation* ani_left_crossUp_gun = new Animation();
	//ani_left_crossUp_gun->Add(new Sprite(21, 3, 29, 11, d3dtex), 1000);

	////Chéo lên - Phải
	//Animation* ani_right_crossUp_gun = new Animation();
	//ani_right_crossUp_gun->Add(new Sprite(381, 3, 389, 11, d3dtexR), 1000);

	////Dọc - Trái
	//Animation* ani_left_vertical_gun = new Animation();
	//ani_left_vertical_gun->Add(new Sprite(32, 3, 36, 10, d3dtex), 1000);

	////Dọc - Phải
	//Animation* ani_right_vertical_gun = new Animation();
	//ani_right_vertical_gun->Add(new Sprite(374, 3, 378, 10, d3dtexR), 1000);


	//--------------- da tao xong animation -----------------------------
	//upright
	LPACTIVITY act_up_right = new Activity(this->animations->GetAnimation(ANIMATIONS::UPRIGHT), this);
	act_up_right->Add(D3DXVECTOR2(0, 0), 100);
	act_up_right->Add(D3DXVECTOR2(-1, -2),100);
	act_up_right->Add(D3DXVECTOR2(-2, -2), 100);
	this->activities->Add(act_up_right);

	//upleft
	LPACTIVITY act_up_left = new Activity(this->animations->GetAnimation(ANIMATIONS::UPLEFT), this);
	act_up_left->Add(D3DXVECTOR2(0, 0), 100);
	act_up_left->Add(D3DXVECTOR2(1, -2), 100);
	act_up_left->Add(D3DXVECTOR2(2, -2), 100);
	this->activities->Add(act_up_left);
}

void Gun::Update(DWORD dt)
{
	this->SetCenterPostion(body->GetCenterPostion() - *move);

	if (SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::IDLERIGHT || SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::WALKRIGHT) {
		this->IdleRight();
	}
	else
	if (SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::IDLELEFT || SOPHIA::GetInstance()->GetStatus() == SOPHIA::ANIMATIONS::WALKLEFT) {
		this->IdleLeft();
		this->SetCenterPostion(body->GetCenterPostion() + *move - *(new D3DXVECTOR2(1, 10)));
	}

	if (animations != NULL)
		animations->Update(dt);

	if (activities != nullptr) {
		activities->Update(dt);
	}
}

void Gun::Render()
{
	if (animations != NULL)
		animations->Render(*wPosition);
}

void Gun::IdleRight()
{
	this->animations->Start(ANIMATIONS::IDLERIGHT);
}

void Gun::IdleLeft()
{
	this->animations->Start(ANIMATIONS::IDLELEFT);
}

void Gun::UpRight()
{
	this->animations->Start(ANIMATIONS::UPRIGHT);
	this->activities->Start(ACTIVITIES::UP_RIGHT);
}

void Gun::UpLeft()
{
	this->animations->Start(ANIMATIONS::UPLEFT);
	this->activities->Start(ACTIVITIES::UP_LEFT);
}

void Gun::DownRight()
{
	this->activities->Resume(-1);
	this->animations->Resume(-1);
}

void Gun::DownLeft()
{
	this->activities->Resume(-1);
	this->animations->Resume(-1);
}

Gun::~Gun()
{
}
