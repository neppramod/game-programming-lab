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

void GameWindow::updateWindowSize(int width, int height)
{
	Win32OGLWindow::updateWindowSize(width, height);
	((OGLRenderer*)this->renderer)->updateViewingFrustum("ShaderProgram3d", 60.0f, this->getAspectRatio(), 1.0f, 45.0f);
	((OGLRenderer*)this->renderer)->updateViewingFrustum("ShaderProgram3dv3", 60.0f, this->getAspectRatio(), 1.0f, 45.0f);
}

LRESULT CALLBACK GameWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	OGLRenderer* renderer = ((OGLRenderer*)self->renderer);

	switch (message) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_F1:
			self->log("Help:");
			self->log(" RIGHT ARROW - Move camera right");
			self->log(" LEFT ARROW - Move camera left");
			self->log(" UP ARROW - Move camera up");
			self->log(" DOWN ARROW - Move camera down");
			self->log(" ESC - Exit");
			break;
		case VK_RIGHT:
			renderer->moveCameraRight();
			break;
		case VK_LEFT:
			renderer->moveCameraLeft();
			break;
		case VK_UP:
			renderer->moveCameraUp();
			break;
		case VK_DOWN:
			renderer->moveCameraDown();
			break;
		case VK_ESCAPE:
			self->log("Exiting!");
			self->exit();
			break;
		}
		return 0;
	}


	return Win32OGLWindow::WndProc(hWnd, message, wParam, lParam);
}
