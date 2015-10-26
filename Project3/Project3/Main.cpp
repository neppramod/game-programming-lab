#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glutilD.lib")

#define CONFIG_FILE_NAME "window.config"

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
#include "LocalLightSource.h"
#include "Configuration.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Configuration *configuration = new Configuration(CONFIG_FILE_NAME);

	GameEngine gameEngine(
		new WindowsConsoleLogger(), 
		new CoreSystem(
			new TextFileReader()), 
		new OGLGraphicsSystem(
			new OGLShaderManager(), 
			new GameWorld(
				new GameObjectManager(),
				new OGLFirstPersonCamera()),
			new OGLViewingFrustum(),
			new LocalLightSource()
			),
		new GameWindow(
			configuration->getTitle(),
			configuration->getWidth(), 
			configuration->getHeight()),
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
	graphics->addVertexShader(
		"VertexShaderIllumination",
		new OGLVertexShader(),
		reader->readContents("VertexShader3DIllumination.glsl"));
	graphics->addFragmentShader(
		"SimpleFragmentShader", 
		new OGLFragmentShader());
	graphics->addFragmentShader(
		"FragmentShaderIllumination",
		new OGLFragmentShader(),
		reader->readContents("FragmentShader3DIllumination.glsl"));

	graphics->addShaderProgram(
		"SimpleShader", 
		new OGLShaderProgram(), 
		"SimpleVertexShader", "SimpleFragmentShader");
	graphics->addShaderProgram(
		"ShaderProgram3d", 
		new OGLShaderProgram(), 
		"VertexShader3d", "SimpleFragmentShader");
	graphics->addShaderProgram(
		"ShaderProgramIllumination",
		new OGLShaderProgram(),
		"VertexShaderIllumination", "FragmentShaderIllumination");

	gameEngine.initializeWindowAndGraphics();

	StockObjectLoader loader;
	loader.loadObjects(graphics->getGameWorld()->getObjectManager());

	graphics->setActiveShaderProgram("ShaderProgramIllumination");
	graphics->setObjectsShaderProgram("ShaderProgramIllumination");
	

	//OGLSphericalCamera *camera = (OGLSphericalCamera *)graphics->getGameWorld()->getCamera();
	//camera->setPosition(25.0f, -30.0f, 30.0f);
	OGLFirstPersonCamera *camera = (OGLFirstPersonCamera *)graphics->getGameWorld()->getCamera();
	camera->setPosition(0.0f, 5.0f, 10.0f);
	


	graphics->setUpViewingEnvironment();

	gameEngine.setupGame();
	gameEngine.run();

	return 0;
}
