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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
		new GameWindow(
			L"The Game Window", 
			1000, 
			800),
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
