#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glutilD.lib")

#include "WindowsConsoleLogger.h"
#include "GameWindow.h"
#include "OGLRenderer.h"
#include "OGLVertexShader.h"
#include "OGLFragmentShader.h"
#include "OGLShaderProgram.h"
#include "OGLShaderManager.h"
#include "TextFileReader.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Logger* logger = new WCLogger();

	TextFileReader reader;
	reader.setLogger(logger);
	string vertexCode = reader.readContents("VertexShader3DPerspective.glsl");

	OGLVertexShader * vertexShader = new OGLVertexShader();
	vertexShader->setLogger(logger);

	OGLVertexShader * vertexShader3d = new OGLVertexShader((GLchar*)vertexCode.c_str());
	vertexShader3d->setLogger(logger);

	string vertexCode2 = reader.readContents("VertexShader3DPerspectiveVec3.glsl");
	OGLVertexShader * vertexShader3dv3 = new OGLVertexShader((GLchar*)vertexCode2.c_str());
	vertexShader3dv3->setLogger(logger);

	OGLFragmentShader * fragmentShader = new OGLFragmentShader();
	fragmentShader->setLogger(logger);

	OGLShaderProgram * shaderProgram = new OGLShaderProgram();
	shaderProgram->setLogger(logger);

	OGLShaderProgram * shaderProgram3d = new OGLShaderProgram();
	shaderProgram3d->setLogger(logger);

	OGLShaderProgram * shaderProgram3dv3 = new OGLShaderProgram();
	shaderProgram3d->setLogger(logger);

	OGLShaderManager * shaderMgr = new OGLShaderManager();
	shaderMgr->addVertexShader("StockVertexShader", vertexShader);
	shaderMgr->addFragmentShader("StockFragmentShader", fragmentShader);
	shaderMgr->addShaderProgram("StockShader", shaderProgram, "StockVertexShader", "StockFragmentShader");
	shaderMgr->addVertexShader("VertexShader3d", vertexShader3d);
	shaderMgr->addShaderProgram("ShaderProgram3d", shaderProgram3d, "VertexShader3d", "StockFragmentShader");
	shaderMgr->addVertexShader("VertexShader3dv3", vertexShader3dv3);
	shaderMgr->addShaderProgram("ShaderProgram3dv3", shaderProgram3dv3, "VertexShader3dv3", "StockFragmentShader");

	Renderer * renderer = new OGLRenderer(shaderMgr);
	renderer->setLogger(logger);

	GameWindow *window = new GameWindow(renderer, L"The Game Window", 1000, 800);
	window->setLogger(logger);

	if (window->create()) {
		if (window->createRenderer()) {
			window->show();
			window->listenForEvents();
		}
	}

	delete window;
	delete renderer;
	delete shaderMgr;
	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	delete logger;
	return 0;
}
