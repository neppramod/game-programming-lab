#pragma once
#ifndef LIGHT_BACK_FORTH_BEHAVIOR
#define LIGHT_BACK_FORTH_BEHAVIOR

#include "IBehavior.h"

class LocalLightSource;

class LightBackForthBehavior 
{
public:
	enum State { MOVING_FORWARD, MOVING_BACKWARD };

protected:
	State state;
	float maxDistance;
	float distanceMoved;
	float intensity;
	float maxIntensity;

public:
	LightBackForthBehavior(float maxDistance = 5.0f);
	virtual ~LightBackForthBehavior();

	void update(LocalLightSource *lightSource, float elapsedSeconds);
};

#endif
