#pragma once
#ifndef FOUR_POINT_PATROL_BEHAVIOR
#define FOUR_POINT_PATROL_BEHAVIOR

#include "IBehavior.h"

class FourPointPatrolBehavior :
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
	FourPointPatrolBehavior(float maxDistance = 10.0f);
	virtual ~FourPointPatrolBehavior();

	void update(GameObject *object, float elapsedSeconds);
};

#endif

