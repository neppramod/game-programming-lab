#include "OGLSphericalCamera.h"
#include "MathUtil.h"

OGLSphericalCamera::OGLSphericalCamera()
{
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->setPosition(5, 0, 0);
}

OGLSphericalCamera::~OGLSphericalCamera()
{
}

void OGLSphericalCamera::update(float elapsedMS)
{

}

void OGLSphericalCamera::setTarget(float x, float y, float z)
{
	this->target = glm::vec3(x, y, z);
}

void OGLSphericalCamera::setPosition(float distanceToTarget, float upDownDegrees, float leftRightDegrees)
{
	this->cameraSpherical.rho = distanceToTarget;
	// phi = 0 and theta = 0 should look down the z-axis
	this->cameraSpherical.phi = DegToRad(upDownDegrees + 90.0f);
	this->cameraSpherical.theta = DegToRad(leftRightDegrees);

	// See http://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates
	// Spherical to Cartesian
	// x = r * sin(theta) * sin(phi)
	// y = r * cos(phi)
	// z = r * cos(theta) * sin(phi)

	float fSinTheta = sinf(this->cameraSpherical.theta);
	float fCosTheta = cosf(this->cameraSpherical.theta);
	float fCosPhi = cosf(this->cameraSpherical.phi);
	float fSinPhi = sinf(this->cameraSpherical.phi);

	glm::vec3 dirToCamera(fSinTheta * fSinPhi, fCosPhi, fCosTheta * fSinPhi);
	glm::vec3 position = (dirToCamera * cameraSpherical.rho) + this->target;

	glm::vec3 lookDir = glm::normalize(this->target - position);

	glm::vec3 upDir = glm::normalize(this->up);

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f); // Negate the look direction to point at the look point

	// Since we are building a world-to-camera matrix, we invert the matrix.
	// Transposing a rotation matrix inverts it!
	rotMat = glm::transpose(rotMat);

	// Translate the camera to the origin
	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-position, 1.0f);

	// Translate and then rotate
	this->orientation = rotMat * transMat;
}
