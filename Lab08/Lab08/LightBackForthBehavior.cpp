#include "LightBackForthBehavior.h"
#include "LocalLightSource.h"

LightBackForthBehavior::LightBackForthBehavior(float maxDistance)
{
	this->state = MOVING_FORWARD;
	this->maxDistance = maxDistance;
	this->distanceMoved = 0;
	this->intensity = 0;
	this->maxIntensity = 1;
}

LightBackForthBehavior::~LightBackForthBehavior()
{
}

void LightBackForthBehavior::update(LocalLightSource *lightSource, float elapsedSeconds)
{
	LocalLightSource* obj = (LocalLightSource*)lightSource;
	float delta = 10.0f * elapsedSeconds;
	this->distanceMoved += delta;
	this->intensity += delta * 0.04;

	glm::vec3 position = lightSource->getPostion();
	glm::vec3 newPosition;

	lightSource->setIntensity(this->intensity);

	// Change intensity
	if (this->intensity >= this->maxIntensity) {
		this->intensity = this->intensity - this->maxIntensity;
	}

	switch (this->state) {
	case MOVING_BACKWARD:
		if (this->distanceMoved >= this->maxDistance) {
			this->state = MOVING_FORWARD;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}		

		newPosition = position;
		newPosition.x -= delta;
		lightSource->setPosition(newPosition);
				
		break;
	case MOVING_FORWARD:
		if (this->distanceMoved >= this->maxDistance) {
			this->state = MOVING_BACKWARD;
			delta = this->distanceMoved - this->maxDistance;
			this->distanceMoved = 0;
		}

		newPosition = position;
		newPosition.x += delta;
		lightSource->setPosition(newPosition);
		break;
	}
}
