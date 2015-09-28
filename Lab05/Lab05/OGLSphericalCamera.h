#pragma once
#ifndef OGL_SPHERICAL_CAMERA
#define OGL_SPHERICAL_CAMERA

#include "Camera.h"
#include "OGLReferenceFrame.h"

#include <glm\glm.hpp>

/**
 Models a Spherical camera, where the camera is circling about a target point always looking
 at that point.
**/
class OGLSphericalCamera :	public Camera
{
protected:
	glm::vec3 up;
	glm::vec3 target;

public:
	// See http://mathworld.wolfram.com/SphericalCoordinates.html
	struct SphericalCoordinate {
		float rho, phi, theta;
	}cameraSpherical;

	glm::mat4 orientation;

public:
	OGLSphericalCamera();
	virtual ~OGLSphericalCamera();

	void update(float elapsedMS);

	void setTarget(float x, float y, float z);

	void setPosition(float distanceToTarget, float upDownDegrees, float leftRightDegrees);

protected:

};

#endif

