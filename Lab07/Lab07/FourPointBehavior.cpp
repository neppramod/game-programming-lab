#include "FourPointBehavior.h"
#include "OGLObject.h"

FourPointBehavior::FourPointBehavior(float maxDistance)
{
	this->state = MOVING_FORWARD;
	this->maxDistance = maxDistance;
	this->distanceMoved = 0;
}

FourPointBehavior::~FourPointBehavior()
{
}

void FourPointBehavior::update(GameObject *object, float elapsedSeconds)
{
	OGLObject* obj = (OGLObject*)object;
	float delta = 5.0f * elapsedSeconds;
	this->distanceMoved += delta;
	switch (this->state) {
	case MOVING_FORWARD:
		if (this->distanceMoved >= this->maxDistance) {
			this->state = MOVING_RIGHT;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}
		obj->referenceFrame.moveForward(delta);
		break;

	case MOVING_RIGHT:
		if (this->distanceMoved >= this->maxDistance) {
			this->state = MOVING_BACKWARD;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}
		obj->referenceFrame.moveRight(delta);
		break;

	case MOVING_BACKWARD:
		if (this->distanceMoved >= this->maxDistance) {
			this->state = MOVING_LEFT;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}
		obj->referenceFrame.moveBackward(delta);
		break;

	case MOVING_LEFT:
		if (this->distanceMoved >= this->maxDistance) {
			this->state = MOVING_FORWARD;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}
		obj->referenceFrame.moveLeft(delta);
		break;
	}	
}
