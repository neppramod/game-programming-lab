#include "FourPointPatrolBehavior.h"
#include "OGLObject.h"

FourPointPatrolBehavior::FourPointPatrolBehavior(float maxDistance)
{
	this->maxDistance = maxDistance;
	this->distanceMoved = 0.0f;
	this->state = MOVING_FORWARD;
	this->maxRotation = 90.0f;
	this->degreesRotated = 0.0f;
	this->totalDistanceMoved = 0.0f;
	this->distanceStop = 10;
	this->distanceStopped = 0.0f;
	
}


FourPointPatrolBehavior::~FourPointPatrolBehavior()
{
}

void FourPointPatrolBehavior::update(GameObject *object, float elapsedSeconds)
{
	OGLObject *obj = (OGLObject *)object;

	
	switch (this->state) {
	case MOVING_FORWARD:
	{
		delta = 5.0f * elapsedSeconds;
		this->distanceMoved += delta;
		this->totalDistanceMoved += delta;
				
		if (this->distanceMoved >= this->maxDistance) {
			this->state = TURN_AROUND;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}		

		obj->referenceFrame.moveForward(delta);
		
		if (totalDistanceMoved >= 2 * this->maxDistance) {
			this->state = STOP;
		}
		
		
		break;
	}

	case STOP: {
		float stopDelta = 5.0f * elapsedSeconds;
		this->distanceStopped += stopDelta;

		if (this->distanceStopped >= this->distanceStop) {
			this->state = MOVING_FORWARD;
			this->totalDistanceMoved = 0.0f;
			stopDelta = this->distanceStopped - this->distanceStop;
			this->distanceStopped = 0;
		}
		obj->referenceFrame.moveForward(0);
		break;
	}

	case TURN_AROUND: {
		float rotateDelta = 90.0f * elapsedSeconds;
		this->degreesRotated += rotateDelta;

		if (this->degreesRotated >= this->maxRotation) {
			this->state = MOVING_FORWARD;
			rotateDelta -= this->degreesRotated - this->maxRotation;
			this->degreesRotated = 0;
		}
				
		obj->referenceFrame.roateLeftWithForwardMovement(rotateDelta, delta * 0.5f);
		break;
	}
	
		

	}

}
