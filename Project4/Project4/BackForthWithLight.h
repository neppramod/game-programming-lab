#pragma once

#ifndef BACK_FORTH_WITH_LIGHT
#define BACK_FORMTH_WITH_LIGHT

#include "IBehavior.h"


#include <vector>

class LightSource;

using namespace std;

class BackForthWithLight:public IBehavior
{

public:
	enum State { MOVING_FORWARD, MOVING_BACKWARD };

protected:
	State state;
	float maxDistance;
	float distanceMoved;	
	LightSource *leftLightSource;
	LightSource *rightLightSource;

public:
	BackForthWithLight(float maxDistance = 10.0f);
	virtual ~BackForthWithLight();
	void update(GameObject *object, float elapsedSeconds);
	void setLeftLightSource(LightSource *lightSource);
	void setRightLightSource(LightSource *lightSource);
};

#endif