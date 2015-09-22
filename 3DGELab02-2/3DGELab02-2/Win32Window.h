#pragma once
#ifndef WIN32_WINDOW
#define WIN32_WINDOW

#include "Windows.h"
#include "GenericWindow.h"

#include <string>
using std::string;
using std::wstring;

class Win32Window :
	public GenericWindow
{
protected:
	wstring title;
	int width, height;
	HWND windowHandle;
	HINSTANCE windowInstance;
	WNDPROC WndProcedure;
	bool timeToExit;

public:
	Win32Window(wstring title, int width, int height);
	virtual ~Win32Window();

	bool create();
	void show();
	void listenForEvents();
	void exit() { this->timeToExit = true; }

protected:
	virtual void runOneFrame() {};
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif

