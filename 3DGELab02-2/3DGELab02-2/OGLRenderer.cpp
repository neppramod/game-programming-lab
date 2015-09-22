#include "OGLRenderer.h"
#include "WindowsConsoleLogger.h"
#include "OGLShaderCompiler.h"
#include "OGLShaderProgram.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

OGLRenderer::OGLRenderer(
	OGLShaderCompiler * vertexShader,
	OGLShaderCompiler * fragmentShader,
	OGLShaderProgram * shaderProgram)
{
	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;
	this->shaderProgram = shaderProgram;

	
	this->objects["SI"] = new OGLObject("SI");
	this->objects["ST"] = new OGLObject("ST");
}

void OGLRenderer::ReadGraphicsFile(string filename, vector<Vertex> & vertices)
{
	ifstream fin;
	fin.open(filename);
	if (fin.fail()) {
		cout << "\nThere was error opening the file." << endl;
		exit(1);
	}

	while (!fin.eof()) {
		Vertex vertex;
		fin >> vertex.x >> vertex.y >> vertex.z >> vertex.red >> vertex.green >> vertex.blue;
		
		if (fin.fail()) {
			break;
		}
		
		vertices.push_back(vertex);
	}
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
		this->createsecondI();
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


void OGLRenderer::createsecondI()
{

	ReadGraphicsFile("drawing1.conf", siVertexData);

	Vertex *slineVertexData = &siVertexData[0];

	VBOObject * lines = OGLObject::createVBOObject("lines");
	lines->buffer = slineVertexData;
	lines->primitiveType = GL_LINES;
	//lines->bufferSizeInBytes = sizeof(*slineVertexData);
	lines->bufferSizeInBytes = 2 * 6 * sizeof(GLfloat);
	lines->numberOfVertices = 2;
	lines->positionComponent.count = 3;
	lines->positionComponent.type = GL_FLOAT;
	lines->positionComponent.bytesToFirst = 0;
	lines->positionComponent.bytesToNext = sizeof(Vertex);
	lines->colorComponent.count = 3;
	lines->colorComponent.type = GL_FLOAT;
	lines->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	lines->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["SI"]->addVBOObject(lines);

	// ST

	VBOObject * triangles = OGLObject::createVBOObject("triangles");
	triangles->buffer = &siVertexData[2];
	triangles->primitiveType = GL_TRIANGLES;
	triangles->bufferSizeInBytes = 3 * 6 * sizeof(GLfloat);
	triangles->numberOfVertices = 3;
	triangles->positionComponent.count = 3;
	triangles->positionComponent.type = GL_FLOAT;
	triangles->positionComponent.bytesToFirst = 0;
	triangles->positionComponent.bytesToNext = sizeof(Vertex);
	triangles->colorComponent.count = 3;
	triangles->colorComponent.type = GL_FLOAT;
	triangles->colorComponent.bytesToFirst = sizeof(GLfloat) * 3;
	triangles->colorComponent.bytesToNext = sizeof(Vertex);
	this->objects["ST"]->addVBOObject(triangles);

}
