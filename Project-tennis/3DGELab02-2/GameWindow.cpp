#include "GameWindow.h"
#include "OGLRenderer.h"

#include <GL\glew.h>

GameWindow *GameWindow::self;

GameWindow::GameWindow(Renderer* renderer, wstring title, int width, int height):
	Win32OGLWindow(title, width, height)
{
	this->renderer = renderer;
	this->WndProcedure = GameWindow::WndProc;
	this->self = this;
}

GameWindow::~GameWindow()
{
}

void GameWindow::runOneFrame()
{
	update();
	render();
}

void GameWindow::update()
{
	this->background.blue += delta;
	if (this->background.blue >= 1.0f || this->background.blue <= 0.0f)
		delta *= -1.0;
}

bool GameWindow::createRenderer()
{
	if(!this->renderer->create()) return false;
	return true;
}

void GameWindow::render()
{

	glViewport(0, 0, this->width, this->height);

	glClearColor(
		this->background.red,
		this->background.green,
		this->background.blue,
		this->background.alpha
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->renderer->renderObjects();

	SwapBuffers(this->deviceContext);
}

LRESULT CALLBACK GameWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Win32OGLWindow::WndProc(hWnd, message, wParam, lParam);
}
