#pragma once
#include <glm\glm.hpp>

class LightBackForthBehavior;

class LocalLightSource
{
protected:
	glm::vec3 position;
	float intensity;
	LightBackForthBehavior* behavior;
public:
	LocalLightSource();
	~LocalLightSource();
	void setPosition(glm::vec3 position) { this->position = position; }
	void setIntensity(float intensity) { this->intensity = intensity; }
	glm::vec3 getPostion() { return this->position; }
	float getIntensity() { return this->intensity;  }
	virtual void update(float elapsedSeconds);
	void setBehavior(LightBackForthBehavior* behavior) { this->behavior = behavior; }
	
};

