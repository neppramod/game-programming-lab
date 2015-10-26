#pragma once
#ifndef OGL_OBJECT
#define OGL_OBJECT

#include <gl/glew.h>
#include <map>

#include <string>
using std::string;
using std::map;

struct Component {
	unsigned int count;
	GLenum type;
	unsigned int bytesToNext;
	unsigned int bytesToFirst;
};

struct VBOObject {
	string name;
	GLuint vbo;
	GLenum primitiveType;
	void * buffer;
	unsigned int bufferSizeInBytes;
	unsigned int numberOfVertices;
	Component positionComponent;
	Component colorComponent;
	VBOObject *next;
};

class OGLObject
{
public:
	string name;
	GLuint vao;

protected:
	map<string, VBOObject *> objects;
	
public:
	OGLObject(string name);
	virtual ~OGLObject();

	void render(GLuint shaderProgramHandle);

	void addVBOObject(VBOObject * object);
	VBOObject * getVBOObject(string name);

	static VBOObject * createVBOObject(string name);

protected:
	GLuint createVBO(GLenum target, const void* bufferData, GLsizei bufferSize);
	void renderObject(GLuint shaderProgramHandle, VBOObject * object);
};

#endif

