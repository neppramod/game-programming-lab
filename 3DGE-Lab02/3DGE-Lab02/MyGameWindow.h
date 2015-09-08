#pragma once
#ifndef MY_GAME_WINDOW
#define MY_GAME_WINDOW

#include "Win32OGLWindow.h"



class MyGameWindow :
	public Win32OGLWindow
{
private:
	struct RGBA {
		float red, green, blue, alpha;
	};

	RGBA background;
	bool positiveChanger = true;
	static MyGameWindow *self;
	float delta = 0.0001f;

	enum COLOR_STATE {
		NO_COLOR, BLACK_RED_BLACK, BLACK_WHITE_BLACK, RED_GREEN_BLUE_RED
	};

	enum TMP_COLOR_STATE {
		RED_GREEN, GREEN_BLUE, BLUE_GREEN, GREEN_RED
	};

	COLOR_STATE currentState;
	TMP_COLOR_STATE tmpColorState;

	void clearScreen(float red, float green, float blue);

public:
	MyGameWindow();
	virtual ~MyGameWindow();
	

protected:
	void runOneFrame();
	void update();
	void render();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif

