#include "Jason.h"

Jason* Jason::_instance = new Jason();

Jason::Jason()
{
	this->direction = 1;
	this->isControlling = false;
	this->maxVelocity = D3DXVECTOR2(0.1, 1);
	this->activities = new Activities();
}

bool Jason::IsAni(int aniid)
{
	if (animations != nullptr) {
		if (this->animations->GetCurrentAnimationID() == aniid)
			return true;
	}
	return false;
}

void Jason::Init()
{
	//texture trái
	LPTEXTURE tex = new Texture(L"textures/BlasterMaster.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtex = tex->LPDIRECT3DTEXTURE();
	//texture phải
	LPTEXTURE texR = new Texture(L"textures/BlasterMaster1.png", D3DCOLOR_XRGB(0, 57, 115));
	LPDIRECT3DTEXTURE9 d3dtexR = texR->LPDIRECT3DTEXTURE();
	
	/// <summary>
	///		Tạo animation
	/// </summary>
	for (int i = 0; i < ANIMATIONS::_lenght; i++)
	{
		switch (i)
		{
		case ANIMATIONS::IDLERIGHT: {
			//đứng yên phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			this->animations->Start(ANIMATIONS::IDLERIGHT);
			break;
		}
		case ANIMATIONS::IDLELEFT: {
			// đứng yên trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKRIGHT: {
			// Đi phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 100);
			ani->Add(new Sprite(381, 30, 389, 46, d3dtexR), 100);
			ani->Add(new Sprite(372, 31, 380, 46, d3dtexR), 100);
			ani->Add(new Sprite(381, 30, 389, 46, d3dtexR), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::WALKLEFT: {
			// Đi trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 100);
			ani->Add(new Sprite(21, 30, 29, 46, d3dtex), 100);
			ani->Add(new Sprite(30, 31, 38, 46, d3dtex), 100);
			ani->Add(new Sprite(21, 30, 29, 46, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::DOWNRIGHT: {
			// Nằm phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(374, 47, 389, 55, d3dtexR), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::DOWNLEFT: {
			// Nằm trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(21, 47, 36, 55, d3dtex), 100);
			this->animations->Add(ani);
			ani->Repeat(true);
			break;
		}
		case ANIMATIONS::CRAWLRIGHT: {
			// Bò phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(374, 47, 389, 55, d3dtexR), 200);
			ani->Add(new Sprite(392, 47, 407, 55, d3dtexR), 200);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::CRAWLLEFT: {
			// Bò trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(21, 47, 36, 55, d3dtex), 200);
			ani->Add(new Sprite(3, 47, 18, 55, d3dtex), 200);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::JUMPRIGHT: {
			// Nhảy phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 200);
			ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 2000);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::JUMPLEFT: {
			// Nhảy trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 200);
			ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 2000);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::DIERIGHT: {
			// Chết phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 100);
			ani->Add(new Sprite(374, 65, 390, 78, d3dtexR), 100);
			ani->Add(new Sprite(358, 64, 371, 80, d3dtexR), 100);
			ani->Add(new Sprite(340, 66, 356, 79, d3dtexR), 100);
			ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 100);
			ani->Add(new Sprite(374, 65, 390, 78, d3dtexR), 100);
			ani->Add(new Sprite(358, 64, 371, 80, d3dtexR), 100);
			ani->Add(new Sprite(340, 66, 356, 79, d3dtexR), 100);
			ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 100);
			ani->Add(new Sprite(374, 65, 390, 78, d3dtexR), 100);
			ani->Add(new Sprite(358, 64, 371, 80, d3dtexR), 100);
			ani->Add(new Sprite(340, 66, 356, 79, d3dtexR), 100);
			ani->Add(new Sprite(393, 64, 406, 80, d3dtexR), 1000);
			ani->Add(new Sprite(392, 83, 407, 97, d3dtexR), 300);
			ani->Add(new Sprite(374, 89, 390, 97, d3dtexR), 500);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::DIELEFT: {
			// Chết trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 100);
			ani->Add(new Sprite(20, 65, 36, 78, d3dtex), 100);
			ani->Add(new Sprite(39, 64, 52, 80, d3dtex), 100);
			ani->Add(new Sprite(54, 66, 70, 79, d3dtex), 100);
			ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 100);
			ani->Add(new Sprite(20, 65, 36, 78, d3dtex), 100);
			ani->Add(new Sprite(39, 64, 52, 80, d3dtex), 100);
			ani->Add(new Sprite(54, 66, 70, 79, d3dtex), 100);
			ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 100);
			ani->Add(new Sprite(20, 65, 36, 78, d3dtex), 100);
			ani->Add(new Sprite(39, 64, 52, 80, d3dtex), 100);
			ani->Add(new Sprite(54, 66, 70, 79, d3dtex), 100);
			ani->Add(new Sprite(4, 64, 17, 80, d3dtex), 1000);
			ani->Add(new Sprite(3, 83, 18, 97, d3dtex), 300);
			ani->Add(new Sprite(20, 89, 36, 97, d3dtex), 500);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::JUMPOUTCARRIGHT: {
			// Nhảy khỏi xe bên phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 400);
			ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 200);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::JUMPOUTCARLEFT: {
			// Nhảy khỏi xe bên trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 400);
			ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 200);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::JUMPINCARRIGHT: {
			// Nhảy vào xe bên phải
			Animation* ani = new Animation();
			ani->Add(new Sprite(399, 30, 407, 46, d3dtexR), 200);
			ani->Add(new Sprite(390, 31, 398, 46, d3dtexR), 400);
			this->animations->Add(ani);
			break;
		}
		case ANIMATIONS::JUMPINCARLEFT: {
			// Nhảy vào xe bên trái
			Animation* ani = new Animation();
			ani->Add(new Sprite(3, 30, 11, 46, d3dtex), 200);
			ani->Add(new Sprite(12, 31, 20, 46, d3dtex), 400);
			this->animations->Add(ani);
			break;
		}
		}
	}

	/// <summary>
	///		Tạo activity
	/// </summary>
	
	//jump out car right
	LPACTIVITY act_jumpoutcar_right = new Activity(this->animations->GetAnimation(ANIMATIONS::JUMPOUTCARRIGHT),this);
	act_jumpoutcar_right->Add(D3DXVECTOR2(0, 2), 200);
	act_jumpoutcar_right->Add(D3DXVECTOR2(0, 2), 200);
	act_jumpoutcar_right->Add(D3DXVECTOR2(0, 2), 200);
	this->activities->Add(act_jumpoutcar_right);

	//jump out car left
	LPACTIVITY act_jumpoutcar_left = new Activity(this->animations->GetAnimation(ANIMATIONS::JUMPOUTCARLEFT), this);
	act_jumpoutcar_right->Add(D3DXVECTOR2(0, 2), 200);
	act_jumpoutcar_right->Add(D3DXVECTOR2(0, 2), 200);
	act_jumpoutcar_right->Add(D3DXVECTOR2(0, 2), 200);
	this->activities->Add(act_jumpoutcar_left);

	//jump in car right
	LPACTIVITY act_jumpincar_right = new Activity(this->animations->GetAnimation(ANIMATIONS::JUMPINCARRIGHT), this);
	act_jumpincar_right->Add(D3DXVECTOR2(0, -2), 200);
	act_jumpincar_right->Add(D3DXVECTOR2(0, -2), 200);
	act_jumpincar_right->Add(D3DXVECTOR2(0, -2), 200);
	this->activities->Add(act_jumpincar_right);

	//jump in car left
	LPACTIVITY act_jumpincar_left = new Activity(this->animations->GetAnimation(ANIMATIONS::JUMPINCARLEFT), this);
	act_jumpincar_left->Add(D3DXVECTOR2(0, -2), 200);
	act_jumpincar_left->Add(D3DXVECTOR2(0, -2), 200);
	act_jumpincar_left->Add(D3DXVECTOR2(0, -2), 200);
	this->activities->Add(act_jumpincar_left);
}

void Jason::Update(DWORD dt)
{
	//DebugOut(L"G: %f  A: %f\n", Global::_G, wAcceleration->y);
	this->ProcessKeyStates();

	Physical(dt);

	if (this->GetBottomPostion().y > 1168.0f) {
		wVelocity->y = 0;
		wAcceleration->y = Global::_G * (-1);
		this->SetBottomPostion(D3DXVECTOR2(this->GetCenterPostion().x, 1168.0f));
		Idle();
	}

	
	if (animations != nullptr) {
		this->animations->Update(dt);
	}

	if (activities != nullptr) {
		this->activities->Update(dt);
	}
}

void Jason::Physical(DWORD dt)
{
	// neu vat ngung di chuyen -> luc ma sat = 0
	if (wVelocity->x == 0) {
		friction = 0;
	}
	// neu vat di chuyen -> luc ma sat nguoc huong voi huong di chuyen
	if (wVelocity->x != 0) {
		friction = (-direction) * Global::_FRICTION;
	}

	//DebugOut(L"ms: %f - Dir: %d  - A: %f\n", friction, direction, wAcceleration->x);

	/// cap nhat van toc theo gia toc
	// van toc x
	this->wVelocity->x += (wAcceleration->x + friction) * dt;
	//van toc y
	this->wVelocity->y += (Global::_G + wAcceleration->y) * dt;

	/// gioi han van toc
	this->wVelocity->x = (abs(wVelocity->x) <= maxVelocity.x) ? wVelocity->x : (direction)*maxVelocity.x;
	this->wVelocity->y = (abs(wVelocity->y) <= maxVelocity.y) ? wVelocity->y : (direction)*maxVelocity.y;

	/// cap nhat toa do theo van toc
	this->wPosition->x += this->wVelocity->x * dt;
	this->wPosition->y += this->wVelocity->y * dt;

	/// gioi han van toc bang 0 khi giam toc
	if (wVelocity->x < 0 && direction == 1)
		StopMove();
	if (wVelocity->x > 0 && direction == -1)
		StopMove();
}

void Jason::Render()
{
	if (animations != nullptr)
		this->animations->Render(*wPosition);
}

void Jason::ProcessKeyStates()
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
		//--Right-Left
		if (keyRight && keyLeft) {
			if (this->status == STATUS::WALK || this->status == STATUS::JUMP) {
				this->wAcceleration->x = 0;
			}
			else
			if (this->status == STATUS::CRAWL) {
				StopMove();
			}
		}
		else
		{
			//--------------------------------KeyRight---------------------------------//
			if (keyRight) {
				if (this->status == STATUS::IDLE) {
					if (direction == 1)
						this->WalkRight();
					else
						this->WalkRight();
				}
				else
				if (this->status == STATUS::JUMP) {
					if (direction == 1)
						this->MoveRight();
					else
						this->MoveRight();
				}
				else
				if (this->status == STATUS::DOWN) {
					if (direction == 1)
						this->CrawlRight();
					else
						this->CrawlRight();
				}
			}
			else
			if (keyLeft) {
				if (this->status == STATUS::IDLE) {
					if (direction == 1)
						this->WalkLeft();
					else
						this->WalkLeft();
				}
				else
					if (this->status == STATUS::JUMP) {
						if (direction == 1)
							this->MoveLeft();
						else
							this->MoveLeft();
					}
					else
						if (this->status == STATUS::DOWN) {
							if (direction == 1)
								this->CrawlLeft();
							else
								this->CrawlLeft();
						}
			}
			else {
				this->wAcceleration->x = 0;
			}
		//--------------------------------KeyLeft---------------------------------//
			
		}

		//--------------------------------KeyUp---------------------------------//

		
		//--------------------------------KeyDown---------------------------------//

		
		//--------------------------------KeyX---------------------------------//


		//--------------------------------Idle---------------------------------//

		
	}

}

bool Jason::GetIsControlling()
{
	return this->isControlling;
}

void Jason::SetIsControlling(bool _isControlling)
{
	this->isControlling = _isControlling;
}



void Jason::Idle()
{
	this->status = STATUS::IDLE;
	if (direction == 1)
		this->animations->Start(ANIMATIONS::IDLERIGHT);
	else
		this->animations->Start(ANIMATIONS::IDLELEFT);
}

void Jason::WalkLeft()
{
	this->direction = -1;
	this->status = STATUS::WALK;
	this->SetAcceleration(D3DXVECTOR2(-0.0005f, this->GetAcceleration().y));
	if (animations != nullptr) {
		animations->Start(ANIMATIONS::WALKLEFT);
	}
}

void Jason::WalkRight()
{
	//DebugOut(L"WalkRight\n");
	this->direction = 1;
	this->status = STATUS::WALK;
	this->SetAcceleration(D3DXVECTOR2(0.0005f, this->GetAcceleration().y));
	if (animations != nullptr){
		animations->Start(ANIMATIONS::WALKRIGHT);
	}
}

void Jason::DownLeft()
{
	this->direction = -1;
	this->status = STATUS::DOWN;
	this->animations->Start(ANIMATIONS::DOWNLEFT);
}

void Jason::DownRight()
{
	this->direction = 1;
	this->status = STATUS::DOWN;
	this->animations->Start(ANIMATIONS::DOWNRIGHT);
}

void Jason::JumpRight()
{
	this->direction = 1;
	this->status = STATUS::JUMP;
	if (this->animations->GetCurrentAnimationID() != ANIMATIONS::JUMPRIGHT) {
		this->SetVelocity(D3DXVECTOR2(0, -0.2f));
		this->animations->Start(ANIMATIONS::JUMPRIGHT);
	}
}

void Jason::JumpLeft()
{
	this->direction = -1;
	this->status = STATUS::JUMP;
	if (this->animations->GetCurrentAnimationID() != ANIMATIONS::JUMPLEFT) {
		this->SetVelocity(D3DXVECTOR2(0, -0.2f));
		this->animations->Start(ANIMATIONS::JUMPLEFT);
	}
}

void Jason::CrawlRight()
{
	this->direction = 1;
	this->wAcceleration->x = 0.0008f;
	this->status = STATUS::CRAWL;
	this->animations->Start(ANIMATIONS::CRAWLRIGHT);
}

void Jason::CrawlLeft()
{
	this->direction = -1;
	this->wAcceleration->x = -0.0008f;
	this->status = STATUS::CRAWL;
	this->animations->Start(ANIMATIONS::CRAWLLEFT);
}

void Jason::DieRight()
{
	this->direction = 1;
	this->status = STATUS::DIE;
	this->animations->Start(ANIMATIONS::DIERIGHT);
}

void Jason::DieLeft()
{
	this->direction = -1;
	this->status = STATUS::DIE;
	this->animations->Start(ANIMATIONS::DIELEFT);
}

void Jason::MoveRight()
{
	if(direction==-1) {
		if (this->status == STATUS::JUMP) {
			this->animations->Start(ANIMATIONS::JUMPLEFT, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
		}
	}
	this->wVelocity->x = 0.08f;
}

void Jason::MoveLeft()
{
	if (direction == 1) {
		if (this->status == STATUS::JUMP) {
			this->animations->Start(ANIMATIONS::JUMPRIGHT, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
		}
	}
	this->wVelocity->x = -0.08f;
}

void Jason::StopMove()
{
	//DebugOut(L"Stop move\n");
	if (this->status == STATUS::WALK) {

		this->Idle();
	}
	else
	if (this->status == STATUS::CRAWL) {
		this->animations->Pause();
		this->status = STATUS::DOWN;
	}
	this->wVelocity->x = 0.0f;
}

Jason* Jason::GetInstance()
{
	if (_instance == NULL) _instance = new Jason();
	return _instance;
}

