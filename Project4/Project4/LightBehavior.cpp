#include "LightBehavior.h"
#include "ObjectGenerator.h"
#include "LightSource.h"
#include <Windows.h>
#include "OGLFirstPersonCamera.h"
#include "OGLObject.h"


LightBehavior::LightBehavior()
{
	this->leftLightSource = NULL;
	this->rightLightSource = NULL;
	this->camera = NULL;
}


LightBehavior::~LightBehavior()
{
}

void LightBehavior::setCamera(OGLFirstPersonCamera *camera)
{
	this->camera = camera;
}

void LightBehavior::setLeftLightSource(LightSource *lightSource)
{
	this->leftLightSource = lightSource;
}

void LightBehavior::setRightLightSource(LightSource *lightSource)
{
	this->rightLightSource = lightSource;
}

void LightBehavior::update(GameObject *object, float elapsedSeconds)
{
	if (this->leftLightSource != NULL && this->rightLightSource != NULL && this->camera != NULL) {
		OGLObject* obj = (OGLObject*)object;
		
		glm::vec3 cameraPosition = this->camera->getPosition();
		glm::vec3 roomPosition = obj->referenceFrame.getPosition();

		if (abs(cameraPosition.x - roomPosition.x) < 5) {
			this->leftLightSource->setIntensity(0.5f);
			this->rightLightSource->setIntensity(0.0f);
		} else if (abs(cameraPosition.x - roomPosition.x) > 5 && abs(cameraPosition.x - roomPosition.x) < 10){
			this->leftLightSource->setIntensity(0.0f);
			this->rightLightSource->setIntensity(0.5f);
		}

		
	}
}
