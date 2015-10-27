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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameEngine gameEngine(
		new WindowsConsoleLogger(), 
		new CoreSystem(
			new TextFileReader()), 
		new OGLGraphicsSystem(
			new OGLShaderManager(), 
			new GameWorld(
				new GameObjectManager(),
				new OGLSphericalCamera()),
			new OGLViewingFrustum()),
		new GameWindow(
			L"The Game Window", 
			1000, 
			800),
		new PCInputSystem(),
		new WindowsTimer()
		);

	OGLGraphicsSystem *graphics = (OGLGraphicsSystem*)gameEngine.getGraphicsSystem();
	TextFileReader *reader = gameEngine.getCoreSystem()->getTextFileReader();

	graphics->addVertexShader(
		"SimpleVertexShader", 
		new OGLVertexShader());
	graphics->addVertexShader(
		"VertexShader3d", 
		new OGLVertexShader(), 
		reader->readContents("VertexShader3DPerspective.glsl"));
	graphics->addFragmentShader(
		"SimpleFragmentShader", 
		new OGLFragmentShader());

	graphics->addShaderProgram(
		"SimpleShader", 
		new OGLShaderProgram(), 
		"SimpleVertexShader", "SimpleFragmentShader");
	graphics->addShaderProgram(
		"ShaderProgram3d", 
		new OGLShaderProgram(), 
		"VertexShader3d", "SimpleFragmentShader");

	gameEngine.initializeWindowAndGraphics();

	StockObjectLoader loader;
	loader.loadObjects(graphics->getGameWorld()->getObjectManager());

	graphics->setActiveShaderProgram("ShaderProgram3d");
	graphics->setObjectsShaderProgram("ShaderProgram3d");

	OGLSphericalCamera *camera = (OGLSphericalCamera *)graphics->getGameWorld()->getCamera();
	camera->setPosition(25.0f, -30.0f, 30.0f);

	graphics->setUpViewingEnvironment();

	gameEngine.setupGame();
	gameEngine.run();

	return 0;
}
