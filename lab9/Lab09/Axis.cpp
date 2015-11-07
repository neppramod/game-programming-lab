#include "Axis.h"
#include "ObjectGenerator.h"


Axis::Axis(const string& name, float length):OGL3DObject(name)
{
	this->length = length;
	this->generate();
}


Axis::~Axis()
{
}


void Axis::generate()
{
	this->setIndexedArrayType();
	ElementArray arr = ObjectGenerator::generateRightHandedAxesIndexedArray(this->length);
	this->setVertexData(arr.vertexData);
	this->setIndexData(arr.indexData);
	VBOObject* vboObject = OGLObject::createVBOObject(
		"Axes", arr.vertexData, arr.indexData, GL_LINES);
	this->addVBOObject(vboObject);

}