#include "OGLObject.h"

#ifndef NULL
#define NULL 0
#endif

OGLObject::OGLObject(string name) : GameObject(name)
{
	this->vao = 0;
	this->setArrayBufferType();
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
	object->vbo = createBufferObject(
		GL_ARRAY_BUFFER, object->buffer, object->bufferSizeInBytes);
	if (this->vboType == INDEXED_ARRAY) {
		object->ibo = createBufferObject(
			GL_ELEMENT_ARRAY_BUFFER, object->indexData, object->indexSizeInBytes);
	}
	
	this->objects[object->name] = object;
	glBindVertexArray(0);
}

void OGLObject::update(float elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

VBOObject * OGLObject::createVBOObject(string name, float* vertexData, GLenum primitiveType)
{
	VBOObject * object = new VBOObject();
	object->name = name;
	object->vbo = 0;
	object->primitiveType = primitiveType;
	object->buffer = &vertexData[1];
	object->bufferSizeInBytes = (unsigned int)vertexData[0] * sizeof(float);
	object->numberOfVertices = (unsigned int)vertexData[0] / sizeof(float) / 2;
	object->indexData = NULL;
	object->indexSizeInBytes = 0;
	object->numberOfIndexes = 0;
	object->positionComponent.type = GL_FLOAT;
	object->positionComponent.count = 4;
	object->positionComponent.bytesToFirst = 0;
	object->positionComponent.bytesToNext = object->positionComponent.count * sizeof(float);
	object->colorComponent.type = GL_FLOAT;
	object->colorComponent.count = 4;
	object->colorComponent.bytesToFirst = 
		sizeof(float) * object->numberOfVertices * object->positionComponent.count;
	object->colorComponent.bytesToNext = object->colorComponent.count * sizeof(float);
	return object;
}

VBOObject* OGLObject::createVBOObject(
	string name, float* vertexData, short* indexData, GLenum primitiveType)
{
	VBOObject * object = new VBOObject();
	object->name = name;
	object->vbo = 0;
	object->primitiveType = primitiveType;
	object->buffer = &vertexData[1];
	object->bufferSizeInBytes = (unsigned int)vertexData[0] * sizeof(float);
	object->numberOfVertices = (unsigned int)vertexData[0] / sizeof(float) / 2;
	object->indexData = &indexData[1];
	object->numberOfIndexes = indexData[0];
	object->indexSizeInBytes = object->numberOfIndexes * sizeof(short);
	object->positionComponent.type = GL_FLOAT;
	object->positionComponent.count = 4;
	object->positionComponent.bytesToFirst = 0;
	object->positionComponent.bytesToNext = 0;
	object->colorComponent.type = GL_FLOAT;
	object->colorComponent.count = 4;
	object->colorComponent.bytesToFirst = 
		sizeof(float) * object->positionComponent.count * object->numberOfVertices;
	object->colorComponent.bytesToNext = 0;
	return object;
}

VBOObject * OGLObject::getVBOObject(string name)
{
	if (this->objects.find(name) != this->objects.end()) {
		return this->objects[name];
	}
	return NULL;
}

GLuint OGLObject::createBufferObject(GLenum target, const void* bufferData, GLsizei bufferSize)
{
	GLuint bufferObjectID = 0;
	glGenBuffers(1, &bufferObjectID);
	glBindBuffer(target, bufferObjectID);
	glBufferData(target, bufferSize, bufferData, GL_STATIC_DRAW);
	glBindBuffer(target, 0);
	return bufferObjectID;
}

void OGLObject::renderObject(VBOObject * object)
{
	glBindVertexArray(this->vao);
	glUseProgram(this->shaderProgram);
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

	if (this->vboType == INDEXED_ARRAY) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ibo);
		glDrawElements(object->primitiveType, object->numberOfIndexes, GL_UNSIGNED_SHORT, 0);
	}
	else {
		glDrawArrays(object->primitiveType, 0, object->numberOfVertices);
	}
	

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
	glBindVertexArray(0);
}

