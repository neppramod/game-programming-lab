#include "OGL3DObject.h"

#include <glm\gtc\type_ptr.hpp>

OGL3DObject::OGL3DObject(const string& name, const string& uniformMatrixName) : 
	OGLObject(name)
{
	this->setUniformMatrixName(uniformMatrixName);
}

OGL3DObject::~OGL3DObject()
{
}

void OGL3DObject::render()
{
	auto iterator = this->objects.begin();
	while (iterator != this->objects.end()) {
		this->sendMatrixToGPU();
		this->renderObject(iterator->second);
		iterator++;
	}
}

void OGL3DObject::sendMatrixToGPU()
{
	auto location =
		glGetUniformLocation(
			this->shaderProgram, this->uniformMatrixName.c_str());

	glUseProgram(this->shaderProgram);
	glUniformMatrix4fv(
		location,
		1,
		GL_FALSE,
		glm::value_ptr(this->referenceFrame.orientation));
	glUseProgram(0);
}