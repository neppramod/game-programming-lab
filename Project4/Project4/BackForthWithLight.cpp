#include "BackForthWithLight.h"
#include "OGLObject.h"
#include "LightSource.h"
#include <windows.h>

BackForthWithLight::BackForthWithLight(float maxDistance)
{
	
	this->state = MOVING_FORWARD;
	this->maxDistance = maxDistance;
	this->distanceMoved = 0;	
	this->leftLightSource = NULL;
	this->rightLightSource = NULL;
}


BackForthWithLight::~BackForthWithLight()
{
}


void BackForthWithLight::update(GameObject *object, float elapsedSeconds)
{	
	if (this->leftLightSource != NULL && this->rightLightSource != NULL) {
		OGLObject* obj = (OGLObject*)object;
		float delta = 5.0f * elapsedSeconds;
		this->distanceMoved += delta;
		switch (this->state) {
		case MOVING_BACKWARD:
			if (this->distanceMoved >= this->maxDistance) {
				this->state = MOVING_FORWARD;
				delta = this->distanceMoved - this->maxDistance;
				this->distanceMoved = 0;
			}

			// Change light
			if (this->distanceMoved >= this->maxDistance / 2) {
				this->leftLightSource->setIntensity(0.5f);
				this->rightLightSource->setIntensity(0.0f);
			}
			

			obj->referenceFrame.moveBackward(delta);
			break;
		case MOVING_FORWARD:
			if (this->distanceMoved >= this->maxDistance) {
				this->state = MOVING_BACKWARD;
				delta = this->distanceMoved - this->maxDistance;
				this->distanceMoved = 0;
			}
			
			// Change light
			if (this->distanceMoved >= this->maxDistance / 2) {
				this->rightLightSource->setIntensity(0.5f);
				this->leftLightSource->setIntensity(0.0f);
			}
			

			obj->referenceFrame.moveForward(delta);
			break;
		}
	}
}

void BackForthWithLight::setLeftLightSource(LightSource *lightSource)
{
	this->leftLightSource = lightSource;
}


void BackForthWithLight::setRightLightSource(LightSource *lightSource)
{
	this->rightLightSource = lightSource;
}