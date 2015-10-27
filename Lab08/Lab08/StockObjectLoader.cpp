#include "StockObjectLoader.h"
#include "OGL3DObject.h"
#include "ObjectGenerator.h"
#include "GameObjectManager.h"

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

	object = new OGL3DObject("Axes");
	object->setIndexedArrayType();
	ElementArray arr = ObjectGenerator::generateRightHandedAxesIndexedArray(5);
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"Axes", arr.vertexData, arr.indexData, GL_LINES);
	object->addVBOObject(vboObject);
	gameObjectManager->addObject("Axes", object);

	//object = new OGL3DObject("Surface");
	//object->setVertexData(ObjectGenerator::generateXZSurface(20, 20));
	//vboObject = OGLObject::createVBOObject(
	//	"triangles", object->getVertexData(), GL_TRIANGLES);
	//object->addVBOObject(vboObject);
	//gameObjectManager->addObject("Surface", object);

	object = new OGL3DObject("Ground");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, 20, 20, { 0.0f, 0.4f, 0.0f, 1.0f });
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

	object = new OGL3DObject("Cuboid");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateCuboid();
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 3.0f);
	object->referenceFrame.rotateY(45);
	gameObjectManager->addObject("Cuboid", object);

	object = new OGL3DObject("Cuboid2");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateCuboid();
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 3.0f);
	object->referenceFrame.rotateY(45);
	gameObjectManager->addObject("Cuboid2", object);

	//object = new OGL3DObject("Red Pyramid");
	//object->setIndexedArrayType();
	//arr = ObjectGenerator::generatePyramidIndexedArray(3, 3, 3, { 1, 0, 0, 1 });
	//object->setVertexData(arr.vertexData);
	//object->setIndexData(arr.indexData);
	//vboObject = OGLObject::createVBOObject(
	//	"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	//object->addVBOObject(vboObject);
	//gameObjectManager->addObject("Red Pyramid", object);

	//object = new OGL3DObject("Line Box");
	//object->setIndexedArrayType();
	//arr = ObjectGenerator::generateLineBoxIndexedArray(3, 3, 3, { 1, 1, 0, 1 });
	//object->setVertexData(arr.vertexData);
	//object->setIndexData(arr.indexData);
	//vboObject = OGLObject::createVBOObject(
	//	"lines", arr.vertexData, arr.indexData, GL_LINES);
	//object->addVBOObject(vboObject);
	//object->referenceFrame.setPosition(0, 1.5f, 0);
	//gameObjectManager->addObject("Line Box", object);

	//for (int i = 0; i < 10; i++) {
	//	float size = rand() % 3 + 1.0f;
	//	float x = rand() % 20 - 10.0f;
	//	float z = rand() % 20 - 10.0f;
	//	float r = (rand() % 100 + 1) / 100.0f;
	//	float g = (rand() % 100 + 1) / 100.0f;
	//	float b = (rand() % 100 + 1) / 100.0f;
	//	string name = "Pyramid" + std::to_string(i + 1);

	//	object = new OGL3DObject(name);
	//	object->setIndexedArrayType();
	//	arr = ObjectGenerator::generatePyramidIndexedArray(
	//		size, size, size, { r, g, b, 1 });
	//	object->setVertexData(arr.vertexData);
	//	object->setIndexData(arr.indexData);
	//	vboObject = OGLObject::createVBOObject(
	//		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	//	object->addVBOObject(vboObject);
	//	object->referenceFrame.setPosition(x, 0.0f, z);
	//	gameObjectManager->addObject(name, object);
	//}
}
