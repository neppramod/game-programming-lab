#include "MyGameWindow.h"
#include <gl\glew.h>
#include <string>

using namespace std;

MyGameWindow *MyGameWindow::self;

MyGameWindow::MyGameWindow() : Win32OGLWindow(L"My Game Window", 600, 600)
{
	this->background.red = 0.0f;
	this->background.green = 0.0f;
	this->background.blue = 0.0f;
	this->background.alpha = 1.0f;
	this->WndProcedure = MyGameWindow::WndProc;
	this->self = this;
}


MyGameWindow::~MyGameWindow()
{
}

void MyGameWindow::runOneFrame()
{
	update();
	render();
}

void MyGameWindow::update()
{	
	switch (currentState) {
	case BLACK_RED_BLACK:
		this->background.red += delta;

		if (this->background.red >= 1.0f || this->background.red <= 0)
			delta *= -1.0;
		break;


	case BLACK_WHITE_BLACK:
		this->background.red += delta;
		this->background.green += delta;
		this->background.blue += delta;

		if (this->background.red >= 1.0f || this->background.red <= 0)
			delta *= -1.0;
		break;

	case RED_GREEN_BLUE_RED:		
		
		switch (tmpColorState) {
		case RED_GREEN:
			this->background.red -= delta;
			this->background.green += delta;
			
			if (this->background.red < 0.0f || this->background.green > 1.0f) {
				clearScreen(0.0f, 1.0f, 0.0f);
				tmpColorState = GREEN_BLUE;
			}
			break;

		case GREEN_BLUE:
			this->background.green -= delta;
			this->background.blue += delta;

			if (this->background.green < 0.0f || this->background.blue > 1.0f) {
				clearScreen(0.0f, 0.0f, 1.0f);
				tmpColorState = BLUE_GREEN;
			}
			break;

		case BLUE_GREEN:
			this->background.blue -= delta;
			this->background.green += delta;			

			if (this->background.blue < 0.0f || this->background.green > 1.0f) {
				clearScreen(0.0f, 1.0f, 0.0f);
				tmpColorState = GREEN_RED;
			}
			break;

		case GREEN_RED:
			this->background.green -= delta;
			this->background.red += delta;

			if (this->background.red > 1.0f || this->background.green < 0.0f) {
				clearScreen(1.0f, 0.0f, 0.0f);
				tmpColorState = RED_GREEN;
			}
			break;
		}

		break;
	
	}
}

void MyGameWindow::clearScreen(float red, float green, float blue)
{
	self->background.red = red;
	self->background.green = green;
	self->background.blue = blue;
}

void MyGameWindow::render()
{
	glViewport(0, 0, this->width, this->height);

	glClearColor(
		this->background.red,
		this->background.green,
		this->background.blue,
		this->background.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	SwapBuffers(this->deviceContext);
}

LRESULT CALLBACK MyGameWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_KEYDOWN:
		
		

		if (wParam == VK_F1) {
			self->log("F2: Black > Red > Black");
			self->log("F3: Black > White > Black");
			self->log("F4: Red > Green > Blue > Green > Red");
			self->log("F5: Show color values");
		}
		else if (wParam == VK_ESCAPE) {
			self->log("Exiting!");
			self->exit();
		}
		else if (wParam == VK_F2) {
			self->currentState = BLACK_RED_BLACK;
			self->clearScreen(0.0f, 0.0f, 0.0f);
			self->update();
		}
		else if (wParam == VK_F3) {
			self->currentState = BLACK_WHITE_BLACK;
			self->clearScreen(0.0f, 0.0f, 0.0f);
			self->update();
		}
		else if (wParam == VK_F4) {
			self->currentState = RED_GREEN_BLUE_RED;
			self->clearScreen(1.0f, 0.0f, 0.0f);		
			self->tmpColorState = RED_GREEN;
			self->update();
		}
		else if (wParam == VK_F5) {
			string colorStr = "Red: " + to_string(self->background.red) + ", Green: " + to_string(self->background.green) + 
				", Blue: " + to_string(self->background.blue);
			self->log(colorStr);
			
		}
		return 0;
	}

	return Win32OGLWindow::WndProc(hWnd, message, wParam, lParam);
}


