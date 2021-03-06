#pragma once
#ifndef GAME_WINDOW
#define GAME_WINDOW

#include "Win32OGLWindow.h"

class Renderer;

class GameWindow :
	public Win32OGLWindow
{
private:
	static GameWindow *self;
	Renderer* renderer;

public:
	GameWindow(Renderer* renderer, wstring title, int width, int height);
	virtual ~GameWindow();

	bool createRenderer();

protected:
	void runOneFrame();
	void update();
	void render();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void updateWindowSize(int width, int height);
};

#endif

