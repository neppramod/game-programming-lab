#include "OGLReferenceFrame.h"

OGLReferenceFrame::OGLReferenceFrame() : orientation(1.0f)
{
}

OGLReferenceFrame::~OGLReferenceFrame()
{
}

void OGLReferenceFrame::setPosition(const glm::vec3& position)
{
	this->orientation[3] = glm::vec4(position, 1.0f);
}

void OGLReferenceFrame::setPosition(float x, float y, float z)
{
	this->orientation[3] = glm::vec4(x, y, z, 1.0f);
}
