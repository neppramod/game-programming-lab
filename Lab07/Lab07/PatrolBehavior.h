#pragma once
#ifndef PATROL_BEHAVIOR
#define PATROL_BEHAVIOR

#include "IBehavior.h"

class PatrolBehavior :
	public IBehavior
{
public:
	enum State { MOVING_FORWARD, TURN_AROUND };

protected:
	State state;
	float maxDistance;
	float distanceMoved;
	float maxRotation;
	float degreesRotated;

public:
	PatrolBehavior(float maxDistance = 10.0f);
	virtual ~PatrolBehavior();

	void update(GameObject *object, float elapsedSeconds);
};

#endif

