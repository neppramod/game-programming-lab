#include "StockObjectLoader.h"
#include "OGL3DObject.h"
#include "ObjectGenerator.h"
#include "GameObjectManager.h"
#include "Cuboid.h"
#include "Turret.h"
#include "Room.h"

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


	object = new Turret("Turret");
	gameObjectManager->addObject("Turret", object);

	object = new Room("Left Room", 10.0f, 10.0f, 10.0f);
	gameObjectManager->addObject("Left Room", object);

	object = new Room("Right Room", 10.0f, 10.0f, 10.0f);
	object->referenceFrame.translate(10.0f, 0.0f, 0.0f);
	object->referenceFrame.rotateY(180.0f);
	gameObjectManager->addObject("Right Room", object);
}
