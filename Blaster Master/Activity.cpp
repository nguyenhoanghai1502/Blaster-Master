#include "Activity.h"

Activity::Activity(LPANIMATION animation,  LPOBJECT object)
{
	this->mode = 1;
	this->currentMovementId = 0;
	this->time = 0;
	this->animation = animation;
	this->movements = movements;
	this->object = object;
}

void Activity::Add(D3DXVECTOR2 d, double time)
{
	;
	if (movements.size() == 0) {
		this->movements.push_back(Movement(d, time));
	}
	else {
		this->movements.push_back(Movement(d, movements.back().time + time));
	}
}

void Activity::Start() {
	if ( isRunning == false) {
		mode = 1;
		time = 0;
		isRunning = true;
		isPausing = false;
		currentMovementId = 0;
	}
}

void Activity::Restart()
{
	mode = 1;
	currentMovementId = 0;
	isRunning = true;
	isPausing = false;
	time = 0;
}


void Activity::Stop() {
	if (isRunning == true) {
		time = 0;
		isRunning = false;
		isPausing = false;
		currentMovementId = 0;
	}
}
void Activity::Pause()
{
	isPausing = true;
}
void Activity::Update(DWORD dt) {
	//DebugOut(L"%d\n", mode);
	if (isRunning) {
		if (mode == 1) {
			if (!isPausing) {
				if (time > movements[currentMovementId].time) {
					object->GetMove()->x += movements[currentMovementId].d.x;
					object->GetMove()->y += movements[currentMovementId].d.y;
					currentMovementId += 1;
				}

				if (currentMovementId >= movements.size()) {
					currentMovementId = movements.size() - 1;
					isPausing = true;
				}
				time = time + dt;
			}
		}
		else
		if (mode == -1) {
			if (!isPausing) {
				if (time < movements[currentMovementId].time) {
					object->GetMove()->x -= movements[currentMovementId].d.x;
					object->GetMove()->y -= movements[currentMovementId].d.y;
					currentMovementId -= 1;
				}
				
				time = time - dt;

				if (currentMovementId < 0) {
					currentMovementId = 0;
					Stop();
				}
				
			}
		}
	}
}

void Activity::Resume(int mode)
{
	if (isRunning) {
		isPausing = false;
		this->mode = mode;
	}
}


Activity::~Activity()
{
}

Movement::Movement(D3DXVECTOR2 d, double time)
{
	this->d = d;
	this->time = time;
}


void Activities::Add(LPACTIVITY activity)
{
	if (activity != nullptr) {
		this->activities.push_back(activity);
	}
	
}

void Activities::Start(int id)
{
	if (id < activities.size()) {
		currentActivityId = id;
		activities[id]->Start();
	}
}

void Activities::Restart( int id)
{
	if (id >= 0 && id < activities.size()) {
		this->currentActivityId = id;
		activities.at(id)->Restart();
	}
}


void Activities::Pause()
{
	if (currentActivityId < activities.size()) {
		activities[currentActivityId]->Pause();
	}
}

void Activities::Resume(int mode)
{
	if (currentActivityId < activities.size()) {
		activities[currentActivityId]->Resume(mode);
	}
}

void Activities::Stop()
{
	if (currentActivityId < activities.size()) {
		activities[currentActivityId]->Stop();
	}
}

void Activities::Update(DWORD dt)
{
	if (currentActivityId < activities.size()) {
		activities[currentActivityId]->Update(dt);
	}

}
