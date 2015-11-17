#include "BackForthWithLight.h"
#include "OGLObject.h"
#include "LightSource.h"
#include <windows.h>
#include "OGLFirstPersonCamera.h"

BackForthWithLight::BackForthWithLight(float maxDistance)
{
	
	this->state = MOVING_FORWARD;
	this->maxDistance = maxDistance;
	this->distanceMoved = 0;	
	this->leftLightSource = NULL;
	this->rightLightSource = NULL;
	this->camera = NULL;
}


BackForthWithLight::~BackForthWithLight()
{
}


void BackForthWithLight::update(GameObject *object, float elapsedSeconds)
{	
	if (this->leftLightSource != NULL && this->rightLightSource != NULL && this->camera != NULL) {
		OGLObject* obj = (OGLObject*)object;
		float delta = 5.0f * elapsedSeconds;
		this->distanceMoved += delta;
		glm::vec3 cameraPosition = this->camera->getPosition();


		switch (this->state) {
		case MOVING_BACKWARD:
			if (this->distanceMoved >= this->maxDistance) {
				this->state = MOVING_FORWARD;
				delta = this->distanceMoved - this->maxDistance;
				this->distanceMoved = 0;
			}

			obj->referenceFrame.moveBackward(delta);
			break;
		case MOVING_FORWARD:
			if (this->distanceMoved >= this->maxDistance) {
				this->state = MOVING_BACKWARD;
				delta = this->distanceMoved - this->maxDistance;
				this->distanceMoved = 0;
			}
			
			obj->referenceFrame.moveForward(delta);
			break;
		}
	}
}

