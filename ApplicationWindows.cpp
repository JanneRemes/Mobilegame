#if defined(WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#include "Application.h"

#include <Windows.h>
#include <iostream>
#include <cassert>
#include "GL\glew.h"
#include <time.h>
#include <random>
#include <array>
LRESULT CALLBACK windowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_CREATE: break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(windowHandle, message, wParam, lParam);
	}
	return 0;
}
class Application::Impl
{


public:

	static const GLuint INDEX_DATA[];

	HGLRC glContext;
	bool running;
	HWND windowHandle;
	MSG message;
	HDC deviceContext;
	void Log(const char *format, va_list arg)
	{


		int done;


		done = vfprintf(stdout, format, arg);


	}
	Impl() {

		WNDCLASSEX window;
		RECT rectangle;
		

		

		window.cbSize = sizeof(window); //muistinvaraus
		window.style = CS_OWNDC; //unique device context, openGL tarvitsee
		window.lpfnWndProc = windowProc; //funktiopointteri
		window.cbClsExtra = 0; //extra muistinvaraus ???
		window.cbWndExtra = 0; //extra muistinvaraus ???
		window.hInstance = GetModuleHandle(nullptr); //exen tiedostopolku?
		window.hIcon = NULL; //ikoni
		window.hCursor = NULL; //kursori
		window.hbrBackground = NULL; //taustan vari
		window.lpszMenuName = L"myMenu";
		window.lpszClassName = L"myWindow";
		window.hIconSm = NULL; //pieni ikoni

		//register window
		assert(RegisterClassEx(&window) != 0);

		//adjust window
		rectangle.left = 100;
		rectangle.top = 100;
		rectangle.right = 800;
		rectangle.bottom = 600;

		assert(AdjustWindowRectEx(&rectangle, WS_CAPTION, false, WS_EX_LEFT) == true);

		//create window
		windowHandle = CreateWindowEx(WS_EX_LEFT, window.lpszClassName, L"myTitle", WS_MINIMIZEBOX | WS_SYSMENU, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, NULL, NULL, window.hInstance, NULL);

		// --> case WM_CREATE ?
		//openGL
		deviceContext = GetDC(windowHandle);

		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cRedBits = 0;
		pfd.cRedShift = 0;
		pfd.cGreenBits = 0;
		pfd.cGreenShift = 0;
		pfd.cBlueBits = 0;
		pfd.cBlueShift = 0;
		pfd.cAlphaBits = 0;
		pfd.cAlphaShift = 0;
		pfd.cAccumBits = 0;
		pfd.cAccumRedBits = 0;
		pfd.cAccumGreenBits = 0;
		pfd.cAccumBlueBits = 0;
		pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.cAuxBuffers = 0;
		pfd.iLayerType = 0;
		pfd.bReserved = 0;
		pfd.dwLayerMask = 0;
		pfd.dwVisibleMask = 0;
		pfd.dwDamageMask = 0;

		int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);

		SetPixelFormat(deviceContext, pixelFormat, &pfd);

		glContext = wglCreateContext(deviceContext);

		wglMakeCurrent(deviceContext, glContext);

		//glViewport(0, 0, rectangle.right, rectangle.bottom);

		// initialize
		assert(glewInit() == GLEW_OK && glGetError() == GL_NO_ERROR);



		//show window
		ShowWindow(windowHandle, SW_SHOWNORMAL);

		//random color
		srand(time(NULL));
		glClearColor(rand() % 10 * 0.1f, rand() % 10 * 0.1f, rand() % 10 * 0.1f, 1);

		running = true;
	
	
	
	
	};

	void Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//piirto loppuu
		SwapBuffers(deviceContext);

		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (message.message == WM_QUIT)
			{
				running = false;
				break;
			}
			DispatchMessage(&message);
		}

	};


	~Impl()
	{
		wglDeleteContext(glContext);
		//assert(UnregisterClass(window.lpszClassName, window.hInstance) == true);
	}
private:

};
int main()
{
	Application a;
	while (true)
	{
		a.Update();
		a.Log("%s", "test");
	}
};
Application::Application() : _impl(new Impl())
{
}

void Application::Update()
{
	_impl->Update();
}
void Application::Log(const char*format,...)
{
	
	va_list arg;

	va_start(arg, format);
	_impl->Log(format, arg);
	va_end(arg);
	
}
Application::~Application()
{
}
#endif