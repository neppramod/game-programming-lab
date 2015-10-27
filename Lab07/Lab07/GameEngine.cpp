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
#include "BackForthBehavior.h"
#include "PatrolBehavior.h"
#include "FourPointPatrolBehavior.h"
#include "FourPointBehavior.h"
#include "FallAndMoveBehavior.h"
#include "OGLObject.h"
#include "OGLReferenceFrame.h"

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

void GameEngine::setupGame()
{
	
	OGLObject* object = (OGLObject*)
		this->graphics->getGameWorld()->getObjectManager()->getObject("Line Box");
	object->referenceFrame.rotateY(-45.0f);
	object->setBehavior(new BackForthBehavior(10));

	
	object = (OGLObject*)
		this->graphics->getGameWorld()->getObjectManager()->getObject("Red Pyramid");
	//object->referenceFrame.rotateY(45.0f);
	object->setBehavior(new BackForthBehavior(15.0f));
	
	
	
	object = (OGLObject*)
		this->graphics->getGameWorld()->getObjectManager()->getObject("Cyan Box");
	object->referenceFrame.rotateY(90.0f);
	object->setBehavior(new PatrolBehavior(5.0f));
	

	
	object = (OGLObject*)
		this->graphics->getGameWorld()->getObjectManager()->getObject("Yellow Box");
	object->referenceFrame.rotateY(30.0f);
	object->setBehavior(new FourPointPatrolBehavior(5.0f));
	

	object = (OGLObject*)
		this->graphics->getGameWorld()->getObjectManager()->getObject("Green Box");	
	object->setBehavior(new FallAndMoveBehavior(5.0f));

	 object = (OGLObject*)
		this->graphics->getGameWorld()->getObjectManager()->getObject("Blue Box");
	object->referenceFrame.rotateY(90.0f);
	object->setBehavior(new FourPointBehavior(5.0f));

	
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


