#include <Windows.h>
#include "GameWorld.h"
#include "GameObjectManager.h"
#include "Camera.h"
#include "PCInputSystem.h"
#include "OGLSphericalCamera.h"
#include "OGLFirstPersonCamera.h"

GameWorld::GameWorld(GameObjectManager *objectManager, Camera *camera)
{
	this->objectManager = objectManager;
	this->camera = camera;
	this->inputSystem = NULL;
}

GameWorld::~GameWorld()
{
	delete this->objectManager;
	delete this->camera;
}

void GameWorld::update(float elapsedSeconds)
{
	this->objectManager->update(elapsedSeconds);
	this->objectManager->updateVisibleObjects();
}

/*
void GameWorld::processInputs()
{
	OGLSphericalCamera *camera = (OGLSphericalCamera*)this->camera;

	camera->setNotMovingLeftRight();
	camera->setNotMovingUpDown();

	if (this->inputSystem->keys[VK_LEFT]) {
		camera->setMovingLeft();
	}
	else if (this->inputSystem->keys[VK_RIGHT]) {
		camera->setMovingRight();
	}

	if (this->inputSystem->keys[VK_UP]) {
		camera->setMovingUp();
	}
	else if (this->inputSystem->keys[VK_DOWN]) {
		camera->setMovingDown();
	}
	
	if (this->inputSystem->isMouseMovingLeft()) {
		camera->setMovingLeft();
	}
	else if (this->inputSystem->isMouseMovingRight()) {
		camera->setMovingRight();
	}

	if (this->inputSystem->isMouseMovingUp()) {
		camera->setMovingUp();
	}
	else if (this->inputSystem->isMouseMovingDown()) {
		camera->setMovingDown();
	}

}
*/

void GameWorld::processInputs()
{
	OGLFirstPersonCamera *camera = (OGLFirstPersonCamera*)this->camera;

	camera->setJustLooking();
	camera->setNotMoving();

	if (this->inputSystem->keys[VK_LEFT]) {
		camera->setLookingLeft();
	}
	else if (this->inputSystem->keys[VK_RIGHT]) {
		camera->setLookingRight();
	}

	if (this->inputSystem->keys[VK_UP]) {
		camera->setLookingUp();
	}
	else if (this->inputSystem->keys[VK_DOWN]) {
		camera->setLookingDown();
	}

	if (this->inputSystem->keys['W']) {
		camera->setMovingForward();
	}
	else if (this->inputSystem->keys['S']) {
		camera->setMovingBackward();
	}
	if (this->inputSystem->keys['A']) {
		camera->setMovingLeft();
	}
	else if (this->inputSystem->keys['D']) {
		camera->setMovingRight();
	}

	if (this->inputSystem->isMouseMovingLeft()) {
		camera->setLookingLeft();
	}
	else if (this->inputSystem->isMouseMovingRight()) {
		camera->setLookingRight();
	}

	if (this->inputSystem->isMouseMovingUp()) {
		camera->setLookingUp();
	}
	else if (this->inputSystem->isMouseMovingDown()) {
		camera->setLookingDown();
	}

}