#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#include <Windows.h>

#include <gl\glew.h>
#include <gl\wglew.h>

#include <string>
using std::string;

#define CONFIG_FILE_NAME "window.config"

#include "Configuration.h"

Configuration *configuration = NULL;

struct WindowStruct
{
	HINSTANCE hInstance;
	HWND hWnd;
};


struct Context {
	HGLRC hrc;
	HDC hdc;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

WindowStruct CreateCustomWindow(const string &title)
{
	WindowStruct window;
	window.hInstance = 0;
	window.hWnd = NULL;


	window.hInstance = GetModuleHandle(NULL);
	if (window.hInstance == 0)
		return window;

	WNDCLASS windowClass;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = window.hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = (LPCWSTR) title.c_str();

	if (!RegisterClass(&windowClass)) {
		window.hInstance = 0;
		window.hWnd = NULL;
		return window;
	}

	window.hWnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		(LPCWSTR) title.c_str(),
		(LPCWSTR) title.c_str(),
		WS_OVERLAPPEDWINDOW,
		configuration->getStartX(),
		configuration->getStartY(),
		configuration->getWidth(),
		configuration->getHeight(),
		NULL,
		NULL,
		window.hInstance,
		NULL
		);

	if (window.hWnd == NULL) {
		window.hInstance = 0;
		window.hWnd = NULL;
	}

	return window;
}

void MessageLoop(const Context &context)
{
	bool timeToExit = false;
	MSG msg;
	while (!timeToExit) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				timeToExit = true;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			glViewport(0, 0, 500, 500);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			SwapBuffers(context.hdc);
		}
	}
}

Context CreateOGLWindow(const WindowStruct &window)
{
	Context context;
	context.hdc = NULL;
	context.hrc = NULL;

	if (window.hWnd == NULL)
		return context;

	context.hdc = GetDC(window.hWnd);
	if (context.hdc == NULL)
		return context;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;

	int pixelFormat = ChoosePixelFormat(context.hdc, &pfd);
	if (pixelFormat == 0) {
		context.hdc = NULL;
		context.hrc = NULL;
		return context;
	}

	BOOL result = SetPixelFormat(context.hdc, pixelFormat, &pfd);
	if (!result) {
		context.hdc = NULL;
		context.hrc = NULL;
		return context;
	}

	HGLRC tempOpenGLContext = wglCreateContext(context.hdc);
	wglMakeCurrent(context.hdc, tempOpenGLContext);

	if (glewInit() != GLEW_OK) {
		context.hdc = NULL;
		context.hrc = NULL;
		return context;
	}

	return context;
}

void ShowWindow(HWND hWnd)
{
	if (hWnd != NULL) {
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}
}

void CleanUp(const WindowStruct &window, const Context &context)
{
	if (context.hdc != NULL) {
		wglMakeCurrent(context.hdc, 0);
		wglDeleteContext(context.hrc);
		ReleaseDC(window.hWnd, context.hdc);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	configuration = new Configuration(CONFIG_FILE_NAME);
	WindowStruct window = CreateCustomWindow(configuration->getTitle());

	if (window.hWnd != NULL) {
		Context context = CreateOGLWindow(window);

		if (context.hdc != NULL) {
			ShowWindow(window.hWnd);

			// Color
			glClearColor(configuration->getColorRed(),
				configuration->getColorGreen(),
				configuration->getColorBlue(),
				0.0f);

			MessageLoop(context);
			CleanUp(window, context);
		}
	}

	delete configuration;

	return 0;
}

