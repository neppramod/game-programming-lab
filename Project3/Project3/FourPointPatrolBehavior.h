#pragma once
#ifndef FOUR_POINT_PATROL_BEHAVIOR
#define FOUR_POINT_PATROL_BEHAVIOR

#include "IBehavior.h"

// Sets up a behavior in which the object moves forward, does a smooth turn and stops at alternate faces of the block
// This behavior is used for the moving vehicle
class FourPointPatrolBehavior :
	public IBehavior
{
public:
	enum State { MOVING_FORWARD, TURN_AROUND, STOP };

protected:
	State state;
	float maxDistance;
	float distanceMoved;
	float maxRotation;
	float degreesRotated;
	float delta;
	
	float totalDistanceMoved;
	float distanceStop;
	float distanceStopped;

	

public:
	FourPointPatrolBehavior(float maxDistance = 10.0f);
	virtual ~FourPointPatrolBehavior();

	void update(GameObject *object, float elapsedSeconds);
};

#endif

