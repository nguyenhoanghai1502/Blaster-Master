#include "Animation.h"
#include "Debug.h"



AnimationFrame::AnimationFrame(LPSPRITE sprite, DWORD time)
{
	this->sprite = sprite;
	this->time = time;
	this->size = D3DXVECTOR2(0, 0);
	this->size = sprite->Size();
}

AnimationFrame::~AnimationFrame()
{
}



Animation::Animation()
{
	listFrames.clear();
	isRepeat = false;
	bool isRunning = false;
	int currentFrameId = 0;
	DWORD time = 0;
	mode = 1;
}

void Animation::Add(LPSPRITE sprite, DWORD time)
{
	if (sprite != NULL) {
		PLANIMATIONFRAME frame;
		if (listFrames.size() == 0)
			frame = new AnimationFrame(sprite, time);
		else
			frame = new AnimationFrame(sprite, listFrames.back()->time + time);
		listFrames.push_back(frame);
	}
}



void Animation::Start()
{
	if (isRunning==false) {
		mode = 1;
		currentFrameId = 0;
		isRunning = true;
		isPausing = false;
		time = 0;
	}
}

void Animation::Restart()
{
	mode = 1;
	currentFrameId = 0;
	isRunning = true;
	isPausing = false;
	time = 0;
}

void Animation::Start(unsigned int frameID, bool contrinues)
{
	if (this->listFrames.size() > 0) {
		this->continues = continues;
		if (continues && isRunning == false) {
			currentFrameId = frameID;
			isRunning = true;
			time = listFrames[currentFrameId]->time;
		}
		if (!continues) {
			currentFrameId = frameID;
			isRunning = true;
			time = listFrames[currentFrameId]->time;
		}
	}
}

void Animation::Reverse()
{
}

void Animation::Stop()
{
	if (this != nullptr) {
		isRunning = true;
		currentFrameId = 0;
	}
}

void Animation::Pause()
{
	isPausing = true;
}

void Animation::Resume(int mode)
{
	if (isRunning && currentFrameId < listFrames.size()) {
		this->mode = mode;
		isPausing = false;
	}
}

void Animation::Repeat(bool isRepeat)
{
	this->isRepeat = isRepeat;
}

void Animation::Update(DWORD dt)
{
	//DebugOut(L"%d\n", mode);
	if (isRunning) {
		if (mode == 1) {
			if (!isPausing) {
				currentFrameId = (time > listFrames[currentFrameId]->time) ? (currentFrameId + 1) : (currentFrameId);
				if (isRepeat == false) {
					if (currentFrameId >= listFrames.size()) {
						currentFrameId = listFrames.size() - 1;
						isPausing = true;
					}
					if (currentFrameId < 0) {
						currentFrameId = 0;
						isPausing = true;
					}
				}
				else {
					time = (currentFrameId > listFrames.size() - 1) ? 0 : (time);
					currentFrameId = (currentFrameId > listFrames.size() - 1) ? 0 : (currentFrameId);
				}

				time = time + dt;
			}
		}
		else
		if(mode == -1){
			if (!isPausing) {
				currentFrameId = (time < listFrames[currentFrameId]->time) ? (currentFrameId - 1) : (currentFrameId);
				if (isRepeat == false) {
					if (currentFrameId >= listFrames.size()) {
						currentFrameId = listFrames.size() - 1;
						isPausing = true;
					}
					if (currentFrameId < 0) {
						currentFrameId = 0;
						isPausing = true;
					}
				}
				else {
					time = (currentFrameId < 0) ? (listFrames[listFrames.size() - 1]->time) : time;
					currentFrameId = (currentFrameId < 0) ? (listFrames.size() - 1) : (currentFrameId);
				}

				time = time - dt;
			}
		}
	}
}

void Animation::UpdateSpeed(double speedrate)
{
	//this->listFrames[currentFrameId]->time = this->listFrames[currentFrameId]->time / (speedrate + 0.5f);
}

bool Animation::IsRunning()
{
	return isRunning;
}

void Animation::Render(D3DXVECTOR2 position, float opacity)
{
	if (listFrames.size() > 0) {
		if (isRunning) {
			PLANIMATIONFRAME frame = listFrames[currentFrameId];
			frame->sprite->Draw(position, opacity);
		}
		
	}
}

RECT Animation::GetSize()
{
	return RECT();
}

unsigned int Animation::GetCurrentFrameID()
{
	return this->currentFrameId;
}

Animation::~Animation()
{
}





Animations::Animations()
{
	listAnimations.clear();
	currentAnimationId = 0;
}

void Animations::Add(LPANIMATION animation)
{
	if (animation != NULL) {
		listAnimations.push_back(animation);
	}
}

void Animations::Start(unsigned int animationID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		this->currentAnimationId = animationID;
		listAnimations.at(animationID)->Start();
	}
}

void Animations::Start(unsigned int animationID, unsigned int frameID, bool continues)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		if (currentAnimationId != animationID)
		{
			this->continues = continues;
			this->listAnimations[currentAnimationId]->Stop();
			this->currentAnimationId = animationID;
			this->listAnimations.at(animationID)->Start(frameID);
		}
	}
}

void Animations::Restart(unsigned int animationID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		this->currentAnimationId = animationID;
		listAnimations.at(animationID)->Restart();
	}
}


void Animations::Pause()
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Pause();
	}
}


void Animations::Resume(int mode)
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Resume(mode);
	}
}

void Animations::Stop()
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Stop();
	}
}

void Animations::Stop(unsigned int animationID)
{
	if (animationID >= 0 && animationID < listAnimations.size()) {
		this->listAnimations.at(animationID)->Stop();
	}
}

void Animations::Update(DWORD dt)
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Update(dt);
	}
}

void Animations::Render(D3DXVECTOR2 position, float opacity)
{
	if (currentAnimationId < listAnimations.size()) {
		listAnimations[currentAnimationId]->Render(position);
	}
}

RECT Animations::GetSize()
{
	if (currentAnimationId < listAnimations.size()) {
		return listAnimations[currentAnimationId]->GetSize();
	}

}

LPANIMATION Animations::GetCurrentAnimation()
{
	return this->listAnimations[currentAnimationId];
}

LPANIMATION Animations::GetAnimation(int id)
{
	if (id < listAnimations.size()) {
		return listAnimations[id];
	}
	return nullptr;
}

int Animations::GetCurrentAnimationID()
{
	return currentAnimationId;
}

Animations::~Animations()
{
}

