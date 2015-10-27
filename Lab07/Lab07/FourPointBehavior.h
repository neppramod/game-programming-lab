#pragma once
#ifndef FOUR_POINT_BEHAVIOR
#define FOUR_POINT_BEHAVIOR

#include "IBehavior.h"

class FourPointBehavior :
	public IBehavior
{
public:
	enum State { MOVING_FORWARD, MOVING_BACKWARD, MOVING_RIGHT, MOVING_LEFT };

protected:
	State state;
	float maxDistance;
	float distanceMoved;

public:
	FourPointBehavior(float maxDistance = 10.0f);
	virtual ~FourPointBehavior();

	void update(GameObject *object, float elapsedSeconds);
};

#endif

