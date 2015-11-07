#include "Cuboid.h"
#include "ObjectGenerator.h"

Cuboid::Cuboid(const string& name, float width, float depth, float height, RGBA faceColor) :
	OGL3DObject(name)
{
	this->width = width;
	this->depth = depth;
	this->height = height;
	this->faceColor = faceColor;
	this->generate();
}

Cuboid::~Cuboid()
{
}

void Cuboid::generate()
{
	this->setIndexedArrayType();
	ElementArray arr = ObjectGenerator::generateCuboid(
		this->width, this->depth, this->height, this->faceColor);
	this->setVertexData(arr.vertexData);
	this->setIndexData(arr.indexData);
	VBOObject* vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	this->addVBOObject(vboObject);
}
