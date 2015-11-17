#pragma once
#ifndef LIGHT_BEHAVIOR
#define LIGHT_BEHAVIOR
#include "IBehavior.h"

class LightSource;
class OGLFirstPersonCamera;

// Change light intensity based on light distance from camera
// I.e. Turn on the light when player enters a room, and turn off when the player leaves the room
class LightBehavior :
	public IBehavior
{
protected:
	LightSource *leftLightSource;
	LightSource *rightLightSource;
	OGLFirstPersonCamera *camera;

public:
	LightBehavior();
	virtual ~LightBehavior();
	void update(GameObject *object, float elapsedSeconds);
	void setCamera(OGLFirstPersonCamera *camera);
	void setLeftLightSource(LightSource *lightSource);
	void setRightLightSource(LightSource *lightSource);
};

#endif
