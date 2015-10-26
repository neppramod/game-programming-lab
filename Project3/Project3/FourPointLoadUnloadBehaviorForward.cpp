#include "FourPointLoadUnloadBehaviorForward.h"

#include "OGLObject.h"


FourPointLoadUnloadBehaviorForward::FourPointLoadUnloadBehaviorForward(float maxDistance)
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


FourPointLoadUnloadBehaviorForward::~FourPointLoadUnloadBehaviorForward()
{
}

void FourPointLoadUnloadBehaviorForward::update(GameObject *object, float elapsedSeconds)
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

		// Check if the opposite block is reached
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

		obj->referenceFrame.moveForward(stopDelta);

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

		//obj->referenceFrame.rotateY(rotateDelta);
		obj->referenceFrame.roateLeftWithForwardMovement(rotateDelta, delta * 0.5f);
		break;
	}



	}

}
