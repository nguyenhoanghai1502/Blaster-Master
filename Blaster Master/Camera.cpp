#include "Camera.h"

Camera::Camera(D3DXVECTOR2 pos, float width, float height)
{
	this->position = pos;
	this->size.y = height;
	this->size.x = width;
	anchorPoint = nullptr;
	limitedZone = nullptr;
}


D3DXVECTOR2 Camera::Position()
{
	return position;
}

D3DXVECTOR2 Camera::Center()
{
	D3DXVECTOR2 c;
	c.x = (2 * position.x + size.x) / 2;
	c.y = (2 * position.y + size.y) / 2;
	return c;
}

D3DXVECTOR2 Camera::Size()
{
	return size;
}

RECT Camera::Border()
{
	RECT box;
	box.left = this->position.x;
	box.top = this->position.y;
	box.right = this->position.x + this->size.x;
	box.bottom = this->position.y + this->size.y;
	return box;
}

void Camera::SetPosition(D3DXVECTOR2 pos)
{
	this->position = pos;
}

void Camera::SetCenter(D3DXVECTOR2 cen)
{
	position.x = cen.x - 0.5 * size.x;
	position.y = cen.y - 0.5 * size.y;
}

void Camera::SetLimitedZone(RECT zone)
{
	long h = zone.right - zone.left;
	long w = zone.bottom - zone.top;
	if (h >= this->size.x && w >= this->size.y) {
		RECT* r = new RECT();
		r->left = zone.left + 1;
		r->top = zone.top;
		r->right = zone.right;
		r->bottom = zone.bottom - 20;
		this->limitedZone = r;
	}
	else
	{
		//DebugOut(L"Camera::SetLimitedZone(TECT zone): parameter 'zone' have size small then camera size.\n");
	}

}

void Camera::AnchorTo(D3DXVECTOR2* point)
{
	this->anchorPoint = point;
}

void Camera::Free()
{
	anchorPoint = nullptr;
}


void Camera::Update(DWORD dt)
{
	if (anchorPoint != nullptr) {
		this->SetCenter(*anchorPoint);

		if (limitedZone != nullptr) {
			if (this->Border().left < limitedZone->left)
				position.x = limitedZone->left;
			if (this->Border().top < limitedZone->top)
				position.y = limitedZone->top;
			if (this->Border().right > limitedZone->right)
				position.x = limitedZone->right - size.x;
			if (this->Border().bottom > limitedZone->bottom)
				position.y = limitedZone->bottom - size.y;
		}
	}
}

//void Camera::ProcessKeyStates(LPKEYBOARD keyboard)
//{
//	if (keyboard->IsKeyDown(DIK_U)) {
//		//DebugOut(L"Keydown: U\n");
//		this->Free();
//	}
//}


D3DXVECTOR2 Camera::Convert(D3DXVECTOR2 pos)
{
	D3DXVECTOR2 cPos;
	cPos.x = pos.x - position.x;
	cPos.y = pos.y - position.y;
	return cPos;
}

Camera::~Camera()
{
}
