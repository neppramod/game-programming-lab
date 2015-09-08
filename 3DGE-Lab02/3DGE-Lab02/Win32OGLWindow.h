#pragma once
#ifndef WIN32_OGL_WINDOW
#define WIN32_OGL_WINDOW

#include "Win32Window.h"

#include <string>
using std::string;

class Win32OGLWindow :
	public Win32Window
{
protected:
	HGLRC renderingContext;
	HDC deviceContext;
	static Win32OGLWindow *self;
	string oglVersion;

public:
	Win32OGLWindow(wstring title, int width, int height);
	virtual ~Win32OGLWindow();

	bool create();

	const string& getOpenGLVersionInformation() const { return this->oglVersion;  }

protected:
	void runOneFrame();
	void updateWindowSize(int width, int height);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif

