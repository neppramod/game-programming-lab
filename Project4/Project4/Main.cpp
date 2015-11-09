#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glutilD.lib")

#include "GameEngine.h"
#include "WindowsConsoleLogger.h"
#include "GameWindow.h"
#include "OGLVertexShader.h"
#include "OGLFragmentShader.h"
#include "OGLShaderProgram.h"
#include "OGLShaderManager.h"
#include "TextFileReader.h"
#include "OGLGraphicsSystem.h"
#include "CoreSystem.h"
#include "GameWorld.h"
#include "GameObjectManager.h"
#include "OGLSphericalCamera.h"
#include "OGLViewingFrustum.h"
#include "StockObjectLoader.h"
#include "PCInputSystem.h"
#include "WindowsTimer.h"
#include "OGLFirstPersonCamera.h"
#include "LightSource.h"
#include "TheGame.h"
#include "Configuration.h"

#define CONFIG_FILE_NAME "window.config"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Read configuration for a file
	Configuration *configuration = new Configuration(CONFIG_FILE_NAME);

	GameEngine gameEngine(
		new WindowsConsoleLogger(), 
		new TheGame(),
		new CoreSystem(
			new TextFileReader()), 
		new OGLGraphicsSystem(
			new OGLShaderManager(), 
			new GameWorld(
				new GameObjectManager(),
				new OGLFirstPersonCamera()),
			new OGLViewingFrustum()),
		new GameWindow(configuration->getTitle(),
			configuration->getWidth(),
			configuration->getHeight()),
		new PCInputSystem(),
		new WindowsTimer()
	);
	gameEngine.loadShaders();
	gameEngine.initializeWindowAndGraphics();
	StockObjectLoader loader;
	gameEngine.setupGame(&loader);
	gameEngine.run();

	return 0;
}
