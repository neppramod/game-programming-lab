#include "StockObjectLoader.h"
#include "OGL3DObject.h"
#include "ObjectGenerator.h"
#include "GameObjectManager.h"
#include "Cuboid.h"
#include "Turret.h"
#include "Axis.h"
#include "Arm.h"
#include "Sword.h"

#include <gl\glew.h>
#include <cstdlib>
#include <ctime>

StockObjectLoader::StockObjectLoader()
{
	srand((unsigned int)time(NULL));
}

StockObjectLoader::~StockObjectLoader()
{
}

void StockObjectLoader::loadObjects(GameObjectManager *gameObjectManager)
{
	OGLObject *object;
	VBOObject* vboObject;

	//object = new OGL3DObject("Axes");
	object = new Axis("Axes", 3.0f);
	gameObjectManager->addObject("Axes", object);
	/*
	object->setIndexedArrayType();
	ElementArray arr = ObjectGenerator::generateRightHandedAxesIndexedArray(5);
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"Axes", arr.vertexData, arr.indexData, GL_LINES);
	object->addVBOObject(vboObject);
	*/
	

	object = new OGL3DObject("Ground");
	object->setIndexedArrayType();
	ElementArray arr = ObjectGenerator::generateFlatSurface(10, 10, 20, 20, { 0.0f, 0.4f, 0.0f, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	gameObjectManager->addObject("Ground", object);

	object = new OGL3DObject("Left Wall");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, 10, 20, { 1.0f, 0.0f, 0.0f, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(-1, 0, 0), 10);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 5);
	object->referenceFrame.rotateZ(-90);
	gameObjectManager->addObject("Left Wall", object);

	object = new OGL3DObject("Back Wall");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, 20, 10, { 1.0f, 0.0f, 0.0f, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(0, 0, -1), 10);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 5);
	object->referenceFrame.rotateX(90);
	gameObjectManager->addObject("Back Wall", object);

	object = new OGL3DObject("Right Wall");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, 10, 20, { 1.0f, 0.0f, 0.0f, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(1, 0, 0), 10);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 5);
	object->referenceFrame.rotateZ(90);
	gameObjectManager->addObject("Right Wall", object);

	object = new OGL3DObject("Roof");
	object->material.shininess = 100;
	object->material.specular = { 1, 1, 1, 1 };
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, 20, 20, { 1.0f, 1.0f, 0.0f, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 10);
	object->referenceFrame.rotateX(180);
	gameObjectManager->addObject("Roof", object);

	/*object = new Cuboid("Cuboid");
	object->referenceFrame.translate(0, 3, -8);
	gameObjectManager->addObject("Cuboid", object);

	object = new Turret("Turret");
	gameObjectManager->addObject("Turret", object);*/

	Sword *katana = new Sword("Katana");
	gameObjectManager->addObject("Katana", katana);

	Arm *arm = new Arm("Left Arm");	
	arm->addSword(katana);
	gameObjectManager->addObject("Left Arm", arm);

	
}
