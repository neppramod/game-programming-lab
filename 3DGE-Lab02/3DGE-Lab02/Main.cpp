#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#include "WindowsConsoleLogger.h"
//#include "Win32OGLWindow.h"
#include "MyGameWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Win32OGLWindow *window = new Win32OGLWindow(L"The Game Window", 500, 500);
	GenericWindow *window = new MyGameWindow();
	window->setLogger(new WCLogger());
	if (window->create()) {

		//window->log(" Hello, World! ");
		//window->log(" Hello, World! ", true);

		window->show();
		window->listenForEvents();
	}
	delete window;
	return 0;
}
