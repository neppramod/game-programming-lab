#pragma once
#ifndef FOUR_POINT_LOAD_UNLOAD_BEHAVIOR_BACKWARD
#define FOUR_POINT_LOAD_UNLOAD_BEHAVIOR_BACKWARD

#include "IBehavior.h"

// Sets up a behavior in which the object moves forward, by following the object with FourPointPatrolBehavior, but when that object stops,
// it goes and does a servillenge of the area (going backward). Once the other object comes to another stop, it comes back and hovers over that object.
// This behavior is used for the servillence cameras
class FourPointLoadUnloadBehaviorBackward :
	public IBehavior
{
public:
	enum State { MOVING_FORWARD, TURN_AROUND, STOP};

protected:
	State state;
	float maxDistance;
	float distanceMoved;
	float maxRotation;
	float degreesRotated;
	float delta;
	
	// Used for transitioning to keep track of vehicle stop state
	float totalDistanceMoved;
	float distanceStop;
	float distanceStopped;

public:
	FourPointLoadUnloadBehaviorBackward(float maxDistance = 10.0f);
	virtual ~FourPointLoadUnloadBehaviorBackward();

	void update(GameObject *object, float elapsedSeconds);
};

#endif

