#include "Keyboard.h"
#include "Debug.h"


Keyboard::Keyboard()
{
	
}

void Keyboard::Init(HWND hWnd)
{
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		//DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		//DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		//DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	//DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void Keyboard::RecordKeyStates(DWORD dt)
{
	for (int i = 0; i < 256; ++i)
		KeyPre[i] = keyStates[i];
	// Collect all key states first

	HRESULT hr;
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				//DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	//keyHandler->KeyState((BYTE*)& keyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		/*if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);*/
	}

	for (int i = 0; i < 256; ++i) {
		keystates[i].value = keyStates[i];
		if (IsKeyUp(i)) {
			keystates[i].holdtime = 0;
		}
		else
		{
			keystates[i].holdtime += dt;
		}
	}
}

bool Keyboard::IsPreKeyDown(int keycode)
{
	return (KeyPre[keycode] & 0x80) > 0;
}


bool Keyboard::IsKeyPress(int keycode)
{
	/*if (IsKeyUp(keycode) && IsPreKeyDown(keycode))
		return true;
	return false;*/
	if (IsKeyDown(keycode) && !IsPreKeyDown(keycode))
		return true;
	return false;
}

bool Keyboard::IsAnyKey()
{
	for (int i = 0; i < 256; i++)
		if (IsKeyPress(i))
			return true;
	return false;
}

bool Keyboard::IsKeyRelease(int  keycode)
{
	if (!IsKeyDown(keycode) && IsPreKeyDown(keycode))
		return true;
	return false;
}

bool Keyboard::IsKeyDown(int keycode)
{
	return (keyStates[keycode] & 0x80);
}

bool Keyboard::IsKeyUp(int keycode)
{
	return !(keyStates[keycode] & 0x80);
}

bool Keyboard::IsHold(int keycode, DWORD holdtime)
{
	if (keystates[keycode].holdtime >= holdtime)
		return true;
	else
		return false;
}

Keyboard::~Keyboard()
{
	if (didv)
	{
		didv->Unacquire();
		didv->Release();
		didv = NULL;
	}
	if (di)
		di->Release();
	di = NULL;
}
