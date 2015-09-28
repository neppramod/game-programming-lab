#include "OGLObject.h"

#ifndef NULL
#define NULL 0
#endif

OGLObject::OGLObject(string name) : GameObject(name)
{
	this->vao = 0;
}

OGLObject::~OGLObject()
{
	for (auto iterator = this->objects.begin(); iterator != this->objects.end(); iterator++) {
		delete iterator->second;
	}
	glDeleteVertexArrays(1, &this->vao);
}

void OGLObject::addVBOObject(VBOObject * object)
{
	if (this->vao == 0) {
		glGenVertexArrays(1, &this->vao);
	}
	glBindVertexArray(this->vao);
	object->vbo = createVBO(GL_ARRAY_BUFFER, object->buffer, object->bufferSizeInBytes);
	this->objects[object->name] = object;
	glBindVertexArray(0);
}

void OGLObject::update(float elapsedMS)
{

}

void OGLObject::render()
{
	for (auto iterator = this->objects.begin(); iterator != this->objects.end(); iterator++) {
		this->renderObject(this->shaderProgram, iterator->second);
	}
}

VBOObject * OGLObject::createVBOObject(string name)
{
	VBOObject * object = new VBOObject();
	object->name = name;
	object->vbo = 0;
	object->primitiveType = GL_LINES;
	object->buffer = NULL;
	object->bufferSizeInBytes = 0;
	object->numberOfVertices = 0;
	object->positionComponent.type = GL_FLOAT;
	object->positionComponent.count = 0;
	object->positionComponent.bytesToFirst = 0;
	object->positionComponent.bytesToNext = 0;
	object->colorComponent.type = GL_FLOAT;
	object->colorComponent.count = 0;
	object->colorComponent.bytesToFirst = 0;
	object->colorComponent.bytesToNext = 0;
	object->next = NULL;

	return object;
}

VBOObject * OGLObject::getVBOObject(string name)
{
	if (this->objects.find(name) != this->objects.end()) {
		return this->objects[name];
	}
	return NULL;
}

GLuint OGLObject::createVBO(GLenum target, const void* bufferData, GLsizei bufferSize)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID);
	glBindBuffer(target, vboID);
	glBufferData(target, bufferSize, bufferData, GL_STATIC_DRAW);
	glBindBuffer(target, 0);
	return vboID;
}

void OGLObject::renderObject(GLuint shaderProgramHandle, VBOObject * object)
{
	glBindVertexArray(this->vao);
	glUseProgram(shaderProgramHandle);
	glBindBuffer(GL_ARRAY_BUFFER, object->vbo);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		object->positionComponent.count,
		object->positionComponent.type,
		GL_FALSE,
		object->positionComponent.bytesToNext,
		(void*)object->positionComponent.bytesToFirst
		);

	// Colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		object->colorComponent.count,
		object->colorComponent.type,
		GL_FALSE,
		object->colorComponent.bytesToNext,
		(void*)object->colorComponent.bytesToFirst
		);

	glDrawArrays(object->primitiveType, 0, object->numberOfVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
	glBindVertexArray(0);
}
