#pragma once

#ifndef ROTATE_Y_BEHAVIOR
#define ROTATE_Y_BEHAVIOR

#include "IBehavior.h"

class RotateYBehavior :
	public IBehavior
{
public:
	enum State {TURN_AROUND};
	

protected:
	State state;
	float maxRotation;
	float degreesRotated;

public:
	RotateYBehavior(float maxDistance);
	~RotateYBehavior();
	void update(GameObject *object, float elapsedSeconds);
};

#endif

