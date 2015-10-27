#pragma once
#ifndef GAME_WORLD
#define GAME_WORLD

class GameObjectManager;
class Camera;
class PCInputSystem;

class GameWorld
{
protected:
	GameObjectManager *objectManager;
	Camera *camera;
	PCInputSystem *inputSystem;

public:
	GameWorld(GameObjectManager *objectManager, Camera *camera);
	virtual ~GameWorld();

	GameObjectManager *getObjectManager() { return this->objectManager; }

	Camera *getCamera() { return this->camera; }

	void setInputSystem(PCInputSystem* inputSystem) { this->inputSystem = inputSystem; }

	virtual void update(float elapsedSeconds);

	virtual void processInputs();

protected:
	
};

#endif

