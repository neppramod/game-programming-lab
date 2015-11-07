#pragma once
#ifndef OGL_OBJECT
#define OGL_OBJECT

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <map>
using std::map;
#include <string>
using std::string;

#include "GameObject.h"
#include "OGLReferenceFrame.h"

struct Component {
	unsigned int count;
	GLenum type;
	unsigned int bytesToNext;
	unsigned int bytesToFirst;
};

struct VBOObject {
	string name;
	GLuint vbo;
	GLuint ibo;
	GLenum primitiveType;
	void * buffer;
	unsigned int bufferSizeInBytes;
	unsigned int numberOfVertices;
	void * indexData;
	unsigned int indexSizeInBytes;
	unsigned int numberOfIndexes;
	Component positionComponent;
	Component colorComponent;
	Component normalComponent;
};

enum VBOType {ARRAY_BUFFER, INDEXED_ARRAY};

class OGLObject : public GameObject
{
public:
	GLuint vao;
	OGLReferenceFrame referenceFrame;

protected:
	map<string, VBOObject *> objects;
	VBOType vboType;
	glm::vec3 speed;
	GLuint shaderProgram;
	
	
public:
	OGLObject(string name);
	virtual ~OGLObject();

	void update(float elapsedSeconds);

	void render() = 0;

	virtual void render(OGLReferenceFrame& frame) = 0;

	void setArrayBufferType() { this->vboType = ARRAY_BUFFER; }

	void setIndexedArrayType() { this->vboType = INDEXED_ARRAY; }

	virtual void setShaderProgram(GLuint shaderProgram) {
		this->shaderProgram = shaderProgram;
	}

	void addVBOObject(VBOObject * object);

	VBOObject * getVBOObject(string name);

	static VBOObject * createVBOObject(string name, float* vertexData, GLenum primitiveType);

	static VBOObject * createVBOObject(
		string name, float* vertexData, short* indexData, GLenum primitiveType = GL_TRIANGLES);

	void setSpeed(float x, float y, float z) { 
		this->speed.x = x;
		this->speed.y = y;
		this->speed.z = z;
	}

	void sendMaterialDataToGPU();

protected:
	GLuint createBufferObject(GLenum target, const void* bufferData, GLsizei bufferSize);

	void renderObject(VBOObject * object);

	void renderVBOObjects();

	
};

#endif

