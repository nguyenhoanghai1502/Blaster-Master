#include "Global.h"
#include "Texture.h"
#include "Debug.h"


Texture::Texture(LPCWSTR filePath, D3DCOLOR transparentColor)
{
	if (Global::GetInstance()->_D3DDV != nullptr) {
		D3DXIMAGE_INFO info;
		HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
		if (result != D3D_OK)
		{
			return;
		}

		result = D3DXCreateTextureFromFileEx(
			Global::GetInstance()->_D3DDV,								// Pointer to Direct3D device object
			filePath,							// Path to the image to load
			info.Width,							// Texture width
			info.Height,						// Texture height
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			transparentColor,
			&info,
			NULL,
			&texture);								// Created texture pointer

		if (result != D3D_OK)
		{
			OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
			return;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture::LPDIRECT3DTEXTURE()
{
	return texture;
}

Texture::~Texture()
{
}

