#pragma once
#include <unordered_map>
#include "Sprite.h"

using namespace std;

class AnimationFrame {
public:
	LPSPRITE sprite;
	DWORD time;
	D3DXVECTOR2 size;
	AnimationFrame(LPSPRITE sprite, DWORD dtime);
	~AnimationFrame();
};
typedef AnimationFrame* PLANIMATIONFRAME;



class Animation {
private:
	std::vector<PLANIMATIONFRAME> listFrames;
	bool isRepeat;
	bool isRunning;
	bool isPausing;
	int currentFrameId;
	int mode;
	bool continues = true;
	DWORD time;
public:
	Animation();
	void Add(LPSPRITE sprite, DWORD time);
	void Start();
	void Restart();
	void Start(unsigned int frameID, bool contrinues = true);
	void Reverse();
	void Stop();
	void Pause();
	void Resume(int mode);
	void Repeat(bool isRepeat);
	void Update(DWORD dt);
	void UpdateSpeed(double speed);
	bool IsRunning();
	void Render(D3DXVECTOR2 position, float opacity = 1.0f);
	RECT GetSize();
	unsigned int GetCurrentFrameID();
	~Animation();
};
typedef Animation* LPANIMATION;



class Animations {
private:
	vector<LPANIMATION> listAnimations;
	int currentAnimationId;
	bool continues = true;
public:
	Animations();
	void Add(LPANIMATION animation);
	void Start(unsigned int id);
	void Restart(unsigned int animationID);
	void Start(unsigned int animationID, unsigned int frameID, bool continues = true);
	void Pause();
	void Resume(int mode);
	void Stop();
	void Stop(unsigned int animationID);
	void Update(DWORD dt);
	void Render(D3DXVECTOR2 position, float opacity = 1.0f);
	RECT GetSize();
	LPANIMATION GetCurrentAnimation();
	LPANIMATION GetAnimation(int id);
	int GetCurrentAnimationID();
	~Animations();
};
typedef Animations* LPANIMATIONS;