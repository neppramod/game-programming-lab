#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#define CONFIG_FILE_NAME "window.config"

#include "WindowsConsoleLogger.h"
#include "GameWindow.h"
#include "OGLRenderer.h"
#include "OGLVertexShader.h"
#include "OGLFragmentShader.h"
#include "OGLShaderProgram.h"
#include "TextFileReader.h"
#include "Configuration.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Logger* logger = new WCLogger();
	Configuration *configuration = new Configuration(CONFIG_FILE_NAME);

	TextFileReader reader;
	reader.setLogger(logger);
	//string vertexCode = reader.readCotents("basicvertexshader.glsl");
	string vertexCode = reader.readCotents("basicvertexshader2.glsl");
	//string vertexCode = reader.readCotents("basicvertexshader3.glsl");

	OGLVertexShader * vertexShader = new OGLVertexShader((GLchar *)vertexCode.c_str());
	vertexShader->setLogger(logger);

	OGLFragmentShader * fragmentShader = new OGLFragmentShader();
	fragmentShader->setLogger(logger);

	OGLShaderProgram * shaderProgram = new OGLShaderProgram();
	shaderProgram->setLogger(logger);

	Renderer * renderer = new OGLRenderer(vertexShader, fragmentShader, shaderProgram);
	renderer->setLogger(logger);
		
	GameWindow *window = new GameWindow(renderer, configuration->getTitle(), configuration->getWidth(), 
		configuration->getHeight());

	window->setLogger(logger);

	if (window->create()) {
		if (window->createRenderer()) {
			window->show();
			window->listenForEvents();
		}
	}

	delete window;
	delete renderer;
	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	delete logger;
	return 0;
}
