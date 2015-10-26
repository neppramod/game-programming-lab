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
	ElementArray arr;

	// Read the graphics data
	core.ReadGraphicsFile(GRAPHICS_FILE, siVertexData);

	int i = 0; // This will help iterate the siVertexData;

	object = new OGL3DObject("Ground");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, siVertexData[i].x, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	gameObjectManager->addObject("Ground", object);
	i++;

	object = new OGL3DObject("Left Wall");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, siVertexData[i].x, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(-1, 0, 0), 10);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 5);
	object->referenceFrame.rotateZ(-90);
	gameObjectManager->addObject("Left Wall", object);
	i++;

	object = new OGL3DObject("Back Wall");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, siVertexData[i].x, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(0, 0, -1), 10);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 5);
	object->referenceFrame.rotateX(90);
	gameObjectManager->addObject("Back Wall", object);
	i++;

	object = new OGL3DObject("Right Wall");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, siVertexData[i].x, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(1, 0, 0), 10);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 5);
	object->referenceFrame.rotateZ(90);
	gameObjectManager->addObject("Right Wall", object);
	i++;

	object = new OGL3DObject("Roof");
	object->material.shininess = 100;
	object->material.specular = { 1, 1, 1, 1 };
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlatSurface(10, 10, siVertexData[i].x, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1.0f });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.move(glm::vec3(0, 1, 0), 10);
	object->referenceFrame.rotateX(180);
	gameObjectManager->addObject("Roof", object);
	i++;

	// First servillence camera
	object = new OGL3DObject("Camera1");  
	object->setIndexedArrayType();	
	arr = ObjectGenerator::generateFlyingSurveillanceCamera(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(0.0f, 1, 0.0f);
	gameObjectManager->addObject("Camera1", object);
	i++;

	// Second servillence camera
	object = new OGL3DObject("Camera2");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateFlyingSurveillanceCamera(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(0.0f, 0.6f, 0.0f);	
	gameObjectManager->addObject("Camera2", object);
	i++;


	// Create house using boxes

	// First house
    object = new OGL3DObject("House1_Lower");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateBoxIndexedArray(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(3.0f, 0.6f, -2.0f);
	gameObjectManager->addObject("House1_Lower", object);
	i++;

	object = new OGL3DObject("House1_Upper");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateBoxIndexedArray(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(3.0f, 1.0f, -2.0f);
	gameObjectManager->addObject("House1_Upper", object);
	i++;

	// Create another house using boxes
	object = new OGL3DObject("House2_Lower");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateBoxIndexedArray(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(3.0f, 0.6f, -3.0f);
	gameObjectManager->addObject("House2_Lower", object);
	i++;

	object = new OGL3DObject("House2_Middle");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateBoxIndexedArray(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(3.0f, 1.0f, -3.0f);
	gameObjectManager->addObject("House2_Middle", object);
	i++;

	object = new OGL3DObject("House2_Upper");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateBoxIndexedArray(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(3.0f, 1.3f, -3.0f);
	gameObjectManager->addObject("House2_Upper", object);
	i++;
	
	// Create a truck
	object = new OGL3DObject("Blue Truck");
	object->setIndexedArrayType();
	arr = ObjectGenerator::generateBoxIndexedArrayTruck(siVertexData[i].x, siVertexData[i].y, siVertexData[i].z, { siVertexData[i].red, siVertexData[i].green, siVertexData[i].blue, 1 });
	object->setVertexData(arr.vertexData);
	object->setIndexData(arr.indexData);
	vboObject = OGLObject::createVBOObject(
		"triangles", arr.vertexData, arr.indexData, GL_TRIANGLES);
	object->addVBOObject(vboObject);
	object->referenceFrame.setPosition(0, 0.1f, 0);
	gameObjectManager->addObject("Blue Truck", object);

}
