#pragma once
#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <string>
using std::string;

class Logger;
class TextFileReader;
class OGLShaderManager;
class OGLVertexShader;
class OGLFragmentShader;
class Renderer;
class GameWindow;
class OGLShaderProgram;
class GraphicsSystem;
class CoreSystem;
class PCInputSystem;
class ITimer;

class GameEngine
{
private:
	Logger *logger;
	CoreSystem *core;
	GraphicsSystem *graphics;
	GameWindow *window;
	PCInputSystem *inputSystem;
	ITimer *timer;
	bool initialized;

public:
	GameEngine(
		Logger *logger, 
		CoreSystem *core, 
		GraphicsSystem *graphics, 
		GameWindow *window,
		PCInputSystem *inputSystem,
		ITimer *timer);

	virtual ~GameEngine();

	GraphicsSystem *getGraphicsSystem() { return this->graphics; }

	CoreSystem *getCoreSystem() { return this->core; }

	PCInputSystem *getInputSystem() { return this->inputSystem; }

	void initializeWindowAndGraphics();

	void setupGame();

	void run();
};

#endif

