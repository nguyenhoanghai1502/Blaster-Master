#pragma once
#include "Object.h"

class Movement {
public:
	Movement(D3DXVECTOR2 d, double time);
	D3DXVECTOR2 d;
	double time;
};

class Activity {
private:
	int mode;
	double time;
	int currentMovementId;
	LPOBJECT object;
	vector<Movement> movements;
	LPANIMATION animation;
	bool isRunning;
	bool isPausing;
public:
	Activity(LPANIMATION animation, LPOBJECT object);
	void Add(D3DXVECTOR2 d, double time);
	void Start();
	void Restart();
	void Stop();
	void Pause();
	void Update(DWORD dt);
	void Resume(int mode);
	~Activity();
};
typedef Activity* LPACTIVITY;

class Activities {
private:
	std::vector<LPACTIVITY> activities;
	int currentActivityId;
public:
	void Add(LPACTIVITY activity);
	void Start(int id);
	void Restart(int id);
	void Pause();
	void Resume(int mode);
	void Stop();
	void Update(DWORD dt);
};
typedef Activities* LPACTIVITIES;