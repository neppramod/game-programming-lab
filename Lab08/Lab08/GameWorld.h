#pragma once
#ifndef GAME_WORLD
#define GAME_WORLD

class GameObjectManager;
class Camera;
class PCInputSystem;
class LocalLightSource;

class GameWorld
{
protected:
	GameObjectManager *objectManager;
	Camera *camera;
	PCInputSystem *inputSystem;
	LocalLightSource *localLightSource;

public:
	GameWorld(GameObjectManager *objectManager, Camera *camera, LocalLightSource *localLightSource);
	virtual ~GameWorld();

	GameObjectManager *getObjectManager() { return this->objectManager; }

	Camera *getCamera() { return this->camera; }

	LocalLightSource *getLocalLightSource() { return this->localLightSource; }

	void setInputSystem(PCInputSystem* inputSystem) { this->inputSystem = inputSystem; }

	virtual void update(float elapsedSeconds);

	virtual void processInputs();

protected:
	
};

#endif

