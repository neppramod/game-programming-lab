#pragma once
#include <glm\glm.hpp>
#include "LocalLightSource.h"

class MovingModulatingLightSource : LocalLightSource
{
public:
	enum State { MOVING_FORWARD, MOVING_BACKWARD };;
	
protected:
	State state;
	float maxDistance;
	float distanceMoved;

public:
	MovingModulatingLightSource(float maxDistance = 10.0f);
	virtual void update(float elapsedSeconds);
};

