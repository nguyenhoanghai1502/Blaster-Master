#pragma once
#include <dinput.h>

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

struct Key
{
public:
	DWORD holdtime;
	BYTE value;
};


class Keyboard
{
private:
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	Key keystates[256];
	BYTE  keyStates[256];			// DirectInput keyboard state buffer
	BYTE KeyPre[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	bool IsPreKeyDown(int keycode);

public:
	Keyboard();
	void Init(HWND hWnd);
	void RecordKeyStates(DWORD dt);
	bool IsAnyKey();
	bool IsKeyPress(int keycode);
	bool IsKeyRelease(int keycode);
	bool IsKeyDown(int keycode);
	bool IsKeyUp(int keycode);
	bool IsHold(int keycode, DWORD holdtime);
	~Keyboard();
};

typedef Keyboard* LPKEYBOARD;

