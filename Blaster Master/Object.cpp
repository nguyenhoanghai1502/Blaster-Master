#include "Object.h"

Object::Object()
{
	this->status = 0;
	this->t = 0;
	this->width = 0;
	this->height = 0;
	this->friction = 0;
	this->wAcceleration = new D3DXVECTOR2(0, 0);
	this->wPosition = new D3DXVECTOR2(0, 0);
	this->wVelocity = new D3DXVECTOR2(0, 0);
	this->move = new D3DXVECTOR2(0, 0);
	this->animations = new Animations();

}

void Object::SetVelocity(D3DXVECTOR2 velocity)
{
	this->wVelocity->x = velocity.x;
	this->wVelocity->y = velocity.y;
}

void Object::SetAcceleration(D3DXVECTOR2 acceleration)
{
	this->wAcceleration->x = acceleration.x;
	this->wAcceleration->y = acceleration.y;
}

void Object::SetCenterPostion(D3DXVECTOR2 center)
{
	if (width >= 0 && height >= 0) {
		wPosition->x = center.x - width / 2;
		wPosition->y = center.y - height / 2;
	}

}

void Object::SetBottomPostion(D3DXVECTOR2 bottom)
{
	if (width >= 0 && height >= 0) {
		wPosition->x = bottom.x - width / 2;
		wPosition->y = bottom.y - height;
	}
}

void Object::SetTopPostion(D3DXVECTOR2 top)
{
	if (width >= 0 && height >= 0) {
		wPosition->x = top.x - width / 2;
		wPosition->y = top.y;
	}
}

void Object::SetLeftPostion(D3DXVECTOR2 left)
{
	if (width >= 0 && height >= 0) {
		wPosition->x = left.x;
		wPosition->y = left.y - height / 2;
	}
}

void Object::SetRightPostion(D3DXVECTOR2 right)
{
	if (width >= 0 && height >= 0) {
		wPosition->x = right.x - width;
		wPosition->y = right.y - height / 2;
	}
}

D3DXVECTOR2 Object::GetVelocity()
{
	return D3DXVECTOR2(wVelocity->x, wVelocity->y);
}

D3DXVECTOR2 Object::GetAcceleration()
{
	return D3DXVECTOR2(wAcceleration->x, wAcceleration->y);
}

D3DXVECTOR2 Object::GetCenterPostion()
{
	return D3DXVECTOR2(wPosition->x + width / 2, wPosition->y + height / 2);
}

D3DXVECTOR2 Object::GetBottomPostion()
{
	return D3DXVECTOR2(wPosition->x + width / 2, wPosition->y + height);
}

D3DXVECTOR2 Object::GetTopPostion()
{
	return D3DXVECTOR2(wPosition->x + width / 2, wPosition->y);
}

D3DXVECTOR2 Object::GetLeftPostion()
{
	return D3DXVECTOR2(wPosition->x, wPosition->y + height / 2);
}

D3DXVECTOR2 Object::GetRightPostion()
{
	return D3DXVECTOR2(wPosition->x + width, wPosition->y + height / 2);
}

LPD3DXVECTOR2 Object::GetMove()
{
	return this->move;
}

LPD3DXVECTOR2 Object::GetPosition()
{
	return this->wPosition;
}

double Object::GetWidth()
{
	return this->width;
}

double Object::GetHeight()
{
	return this->height;
}

RECT Object::GetCollisionBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

RECT Object::GetHitBox()
{
	RECT r;
	r.left = wPosition->x;
	r.right = wPosition->x + width;
	r.top = wPosition->y;
	r.bottom = wPosition->y + height;
	return r;
}

int Object::GetStatus()
{
	return this->status;
}

bool Object::IsExist()
{
	return false;
}


void Object::Init()
{
}

void Object::Physical(DWORD dt)
{

}

void Object::Update(DWORD dt)
{

}

void Object::Render()
{
	if (isExist && animations != NULL) {

	}
}



