#include "FallAndMoveBehavior.h"
#include "OGLObject.h"

#include <cstdlib>
#include <ctime>



FallAndMoveBehavior::FallAndMoveBehavior(float maxDistance)
{	
	this->distanceMoved = 0.0f;
	this->state = RESET;
	this->maxRotation = rand() % 46 + 45;
	this->maxFall = 10;
	this->distanceFallen = 0;

	// Call this once
	srand((unsigned int)time(NULL));

	this->maxDistance = rand() % 11 + 5;

}


FallAndMoveBehavior::~FallAndMoveBehavior()
{
}

void FallAndMoveBehavior::update(GameObject *object, float elapsedSeconds)
{
	OGLObject *obj = (OGLObject *)object;
	

	glm::vec3 position = obj->referenceFrame.getPosition();


	switch (this->state) {
	case RESET: {
		obj->referenceFrame.setPosition(0, 10, 0);
		this->state = FALLING;
		break;
	}
	case FALLING: {
		float delta = 5.0f * elapsedSeconds;
		this->distanceFallen += delta;

		if (this->distanceFallen >= this->maxFall || position.y <= 0) {
			delta = this->distanceFallen - this->maxFall;
			this->distanceFallen = 0;
			obj->referenceFrame.setPosition(0, 0, 0);			
			this->state = MOVING;
		}
		obj->referenceFrame.moveDown(delta);
		break;
	}

	case MOVING:
	{
		float delta = 20.0f * elapsedSeconds;
		this->distanceMoved += delta;

		if (this->distanceMoved >= this->maxDistance || position.x > 20 || position.z > 20 || position.x < -20 || position.z < -20) {
			obj->referenceFrame.setPosition(0, 10, 0);
			this->maxRotation = rand() % 46 + 45; // For next rotation
			obj->referenceFrame.rotateY(maxRotation);
			this->distanceMoved = 0;
			this->state = FALLING;
			this->maxDistance = rand() % 11 + 5; // Max for next movement			
		}
		obj->referenceFrame.moveForward(delta);
		break;
	}
	}
	
}