#include "RotateYBehavior.h"
#include "OGLObject.h"



RotateYBehavior::RotateYBehavior(float maxDistance)
{
	this->state = TURN_AROUND;
	this->maxRotation = 360.0f;
	this->degreesRotated = 0.0f;
}


RotateYBehavior::~RotateYBehavior()
{
}

void RotateYBehavior::update(GameObject *object, float elapsedSeconds)
{
	OGLObject *obj = (OGLObject *)object;

	switch (this->state) {
	case TURN_AROUND: {
		float rotateDelta = 90.0f * elapsedSeconds;
		this->degreesRotated += rotateDelta;

		if (this->degreesRotated >= this->maxRotation) {
			//this->state = MOVING_FORWARD;
			rotateDelta -= this->degreesRotated - this->maxRotation;
			this->degreesRotated = 0;
		}

		obj->referenceFrame.rotateY(rotateDelta);
		break;
	}
	}
}