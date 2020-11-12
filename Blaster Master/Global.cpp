#include "Global.h"

Global* Global::_instance = NULL;
double Global::_FPS = 120;
double Global::_G = 0.00096f;
double Global::_FRICTION = 0.0002f;


Global* Global::GetInstance()
{
	if (_instance == NULL) _instance = new Global();
	return _instance;
}

