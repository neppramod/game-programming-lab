#pragma once
#ifndef FALL_AND_MOVE_BEHAVIOR
#define FALL_AND_MOVE_BEHAVIOR

#include "IBehavior.h"

class FallAndMoveBehavior :
	public IBehavior
{
public:
	enum State { MOVING, FALLING, RESET };

protected:
	State state;
	float maxDistance;
	float minDistance;
	float distanceMoved;
	float maxFall;
	float distanceFallen;
	float maxRotation;
	float degreesRotated;		

public:
	FallAndMoveBehavior(float maxDistance = 10.0f);
	virtual ~FallAndMoveBehavior();

	void update(GameObject *object, float elapsedSeconds);
};

#endif


