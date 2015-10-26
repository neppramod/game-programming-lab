#include "OGLRenderer.h"
#include "WindowsConsoleLogger.h"
#include "OGLShaderCompiler.h"
#include "OGLShaderProgram.h"

#define GRAPHICS_FILE "drawing.dat"

#include <cstdlib>


OGLRenderer::OGLRenderer(
	OGLShaderCompiler * vertexShader,
	OGLShaderCompiler * fragmentShader,
	OGLShaderProgram * shaderProgram)
{
	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;
	this->shaderProgram = shaderProgram;

	
	this->objects["points"] = new OGLObject("points");
	this->objects["court"] = new OGLObject("court");
	this->objects["lines"] = new OGLObject("lines");
	this->objects["poles"] = new OGLObject("poles");
	this->objects["net"] = new OGLObject("net");
	this->objects["flags"] = new OGLObject("flags");
}

OGLRenderer::~OGLRenderer(void)
{
	for (auto iterator = objects.begin(); iterator != objects.end(); iterator++) {
		delete iterator->second;
	}
}

bool OGLRenderer::create()
{
	if (this->setupShaders()) {
		this->createUI();
		return true;
	}
	return false;
}

void OGLRenderer::renderObjects()
{
	for (auto iterator = objects.begin(); iterator != objects.end(); iterator++) {
		iterator->second->render(this->shaderProgram->getHandle());
	}
}

bool OGLRenderer::setupShaders()
{
	bool result = false;
	result = this->vertexShader->compile();
	if (!result) return false;

	result = this->fragmentShader->compile();
	if (!result) return false;

	return this->shaderProgram->link(
		this->vertexShader->getHandle(), 
		this->fragmentShader->getHandle()
		);
}

// Create UI
void OGLRenderer::createUI()
{
	core.ReadGraphicsFile(GRAPHICS_FILE, siVertexData);
	int vertexSize = 6 * sizeof(GLfloat);

	// Create two points (2 vertices)
	VBOObject * points = OGLObject::createVBOObject("points");
	points->buffer = &siVertexData[0]; // Starting at 7th line
	points->primitiveType = GL_POINTS;
	points->bufferSizeInBytes = 2 * vertexSize;
	points->numberOfVertices = 2;
	points->positionComponent.count = 3;
	points->positionComponent.type = GL_FLOAT;
	points->positionComponent.bytesToFirst = 0;
	points->positionComponent.bytesToNext = sizeof(Vertex);
	points->colorComponent.count = 3;
	points->colorComponent.type = GL_FLOAT;
	points->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	points->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["points"]->addVBOObject(points);

	// Create court (6 vertices)
	VBOObject * trianglesCourt = OGLObject::createVBOObject("trianglesCourt");
	trianglesCourt->buffer = &siVertexData[2]; // 6 data for court
	trianglesCourt->primitiveType = GL_TRIANGLES;
	trianglesCourt->bufferSizeInBytes = 6 * vertexSize;
	trianglesCourt->numberOfVertices = 6;
	trianglesCourt->positionComponent.count = 3;
	trianglesCourt->positionComponent.type = GL_FLOAT;
	trianglesCourt->positionComponent.bytesToFirst = 0;
	trianglesCourt->positionComponent.bytesToNext = sizeof(Vertex);
	trianglesCourt->colorComponent.count = 3;
	trianglesCourt->colorComponent.type = GL_FLOAT;
	trianglesCourt->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	trianglesCourt->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["court"]->addVBOObject(trianglesCourt);

	// Court lines (3 lines = 6 vertices)
	VBOObject * lines = OGLObject::createVBOObject("lines");
	lines->buffer = &siVertexData[8]; // 6 data for 3 lines
	lines->primitiveType = GL_LINES;
	lines->bufferSizeInBytes = 6 * vertexSize;
	lines->numberOfVertices = 6;
	lines->positionComponent.count = 3;
	lines->positionComponent.type = GL_FLOAT;
	lines->positionComponent.bytesToFirst = 0;
	lines->positionComponent.bytesToNext = sizeof(Vertex);
	lines->colorComponent.count = 3;
	lines->colorComponent.type = GL_FLOAT;
	lines->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	lines->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["lines"]->addVBOObject(lines);

	// Create two poles (4 vertices)
	VBOObject * poles = OGLObject::createVBOObject("poles");
	poles->buffer = &siVertexData[14]; // 4 data for 2 poles
	poles->primitiveType = GL_LINES;
	poles->bufferSizeInBytes = 4 * vertexSize;
	poles->numberOfVertices = 4;
	poles->positionComponent.count = 3;
	poles->positionComponent.type = GL_FLOAT;
	poles->positionComponent.bytesToFirst = 0;
	poles->positionComponent.bytesToNext = sizeof(Vertex);
	poles->colorComponent.count = 3;
	poles->colorComponent.type = GL_FLOAT;
	poles->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	poles->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["poles"]->addVBOObject(poles);

	// Create net (Two triangles = 6 vertices)
	VBOObject * net = OGLObject::createVBOObject("net");
	net->buffer = &siVertexData[18]; // 6 data for net
	net->primitiveType = GL_TRIANGLES;
	net->bufferSizeInBytes = 6 * vertexSize;
	net->numberOfVertices = 6;
	net->positionComponent.count = 3;
	net->positionComponent.type = GL_FLOAT;
	net->positionComponent.bytesToFirst = 0;
	net->positionComponent.bytesToNext = sizeof(Vertex);
	net->colorComponent.count = 3;
	net->colorComponent.type = GL_FLOAT;
	net->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	net->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["net"]->addVBOObject(net);

	// Create flags (Two triangles = 6 vertices)
	
	VBOObject * flags = OGLObject::createVBOObject("flags");
	flags->buffer = &siVertexData[24]; // 6 data for flags
	flags->primitiveType = GL_TRIANGLES;
	flags->bufferSizeInBytes = 6 * vertexSize;
	flags->numberOfVertices = 6;
	flags->positionComponent.count = 3;
	flags->positionComponent.type = GL_FLOAT;
	flags->positionComponent.bytesToFirst = 0;
	flags->positionComponent.bytesToNext = sizeof(Vertex);
	flags->colorComponent.count = 3;
	flags->colorComponent.type = GL_FLOAT;
	flags->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	flags->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["flags"]->addVBOObject(flags);
	
}
