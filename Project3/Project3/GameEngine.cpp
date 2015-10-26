#include "GameEngine.h"
#include "Logger.h"
#include "OGLShaderManager.h"
#include "GameWindow.h"
#include "GraphicsSystem.h"
#include "CoreSystem.h"
#include "PCInputSystem.h"
#include "GameWorld.h"
#include "ITimer.h"
#include "GameObjectManager.h"
#include "OGLObject.h"
#include "OGLReferenceFrame.h"
#include "RotateYBehavior.h"
#include "FourPointPatrolBehavior.h"
#include "LocalLightSource.h"
#include "PatrolBehavior.h"
#include "FourPointLoadUnloadBehaviorBackward.h"
#include "FourPointLoadUnloadBehaviorForward.h"

GameEngine::GameEngine(
	Logger *logger,
	CoreSystem *core, 
	GraphicsSystem *graphics, 
	GameWindow *window,
	PCInputSystem *inputSystem,
	ITimer *timer)
{
	this->logger = logger;

	this->core = core;
	this->core->setLogger(this->logger);

	this->graphics = graphics;
	this->graphics->setLogger(this->logger);

	this->window = window;
	this->window->setLogger(this->logger);
	this->window->setGameEngine(this);

	this->inputSystem = inputSystem;
	this->graphics->getGameWorld()->setInputSystem(this->inputSystem);

	this->timer = timer;

	this->initialized = false;
}

GameEngine::~GameEngine()
{
	delete this->logger;
	delete this->core;
	delete this->graphics;
	delete this->window;
	delete this->inputSystem;
	delete this->timer;
}

void GameEngine::initializeWindowAndGraphics()
{
	// First create the window
	this->initialized = this->window->create();
	if (this->initialized) {
		// Next, intialize the graphics system
		this->initialized = this->graphics->initialize();
	}
}

// Add behavior to different graphics objects for the animation
void GameEngine::setupGame()
{
	OGLObject* object = (OGLObject*)this->graphics->getGameWorld()->getObjectManager()->getObject("Blue Truck");
	object->referenceFrame.rotateY(90.0f);
	object->setBehavior(new FourPointPatrolBehavior(6.0f));

	object = (OGLObject*)this->graphics->getGameWorld()->getObjectManager()->getObject("Camera1");
	object->referenceFrame.rotateY(90.0f);	
	object->setBehavior(new FourPointLoadUnloadBehaviorBackward(6.0f));

	
	object = (OGLObject*)this->graphics->getGameWorld()->getObjectManager()->getObject("Camera2");
	object->referenceFrame.rotateY(90.0f);
	object->setBehavior(new FourPointLoadUnloadBehaviorForward(6.0f));
	

	LocalLightSource *localLightSource = (LocalLightSource *)
		this->graphics->getLocalLightSource();

	localLightSource->setPosition(glm::vec3(0, 9, 0));
	localLightSource->setIntensity(0.2f);
	
}

void GameEngine::run()
{
	if (this->initialized){
		this->window->show();
		this->window->listenForEvents(this->timer);
	}
	else {
		if (this->logger) {
			this->logger->log("The engine was not initialized!");
		}
	}
}


