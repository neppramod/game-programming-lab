#include "PatrolBehavior.h"
#include "OGLObject.h"


PatrolBehavior::PatrolBehavior(float maxDistance)
{
	this->maxDistance = maxDistance;
	this->distanceMoved = 0.0f;
	this->state = MOVING_FORWARD;
	this->maxRotation = 180.0f;
	this->degreesRotated = 0.0f;
}


PatrolBehavior::~PatrolBehavior()
{
}

void PatrolBehavior::update(GameObject *object, float elapsedSeconds)
{
	OGLObject *obj = (OGLObject *)object;

	switch (this->state) {
	case MOVING_FORWARD:
	{
		float delta = 5.0f * elapsedSeconds;
		this->distanceMoved += delta;

		if (this->distanceMoved >= this->maxDistance) {
			this->state = TURN_AROUND;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}

		obj->referenceFrame.moveForward(delta);
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

		obj->referenceFrame.rotateY(rotateDelta);
		break;
	}

	}

}