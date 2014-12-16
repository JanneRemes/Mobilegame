//#if defined(ANDROID)
#include "Application.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <assert.h>
#include "ResourceManager.h"
static bool graphicInitialized;
class Application::Impl
{

public:
		//from previos




		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;
			bool isRunning = true;
		
		Impl(){ graphicInitialized= false; };
			android_app* application;
	android_poll_source* eventSource;
		~Impl()
	{
		destroyGraphicsContext(application);
	}
	void Initialize(android_app* application)
	{

		this->application = application;
		application->userData = this;
		application->onAppCmd = processCommand;
		application->onInputEvent = processInput;
		isRunning = true;

	}

	static void Log(const char *format, va_list arg)
	{
		__android_log_vprint(ANDROID_LOG_INFO, "NativeSample",
			format, arg);
	}
	static void Log(const char *format, ...)
	{
		va_list arg;

		va_start(arg, format);

		Log(format, arg);
		va_end(arg);
	}

	void Update()
	{
		//Log("%s", "Test1");
		while (ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
		{
			//Log("%s", "Test2");
			if (eventSource != nullptr)
				eventSource->process(application, eventSource);
			//Log("%s", "Test3");
			if (application->destroyRequested != 0)
			{
				//Log("%s", "Test4");
				isRunning = false;
				break;
			}
			//Log("%s", "Test5");
		
	}


	}
	
	

	static void processCommand(android_app* application, int command)
	{
		switch (command)
		{
			
		case APP_CMD_INIT_WINDOW:
			createGraphicsContext(application);
			break;
			/*
		case APP_CMD_TERM_WINDOW:
			destroyGraphicsContext(application);
			break;
			*/
		case APP_CMD_RESUME:
			Log("%s","RESUME");
			break;

		case APP_CMD_PAUSE:
			Log("%s","PAUSE");
			break;

		default:
			break;
		}
	}
	static int processInput(struct android_app* application, AInputEvent* inputEvent)
	{
		//struct data* tempData = (struct data*)application->userData;
		Impl *tempData = static_cast<Impl*>(application->userData);
		switch (AInputEvent_getType(inputEvent))
		{
		case AINPUT_EVENT_TYPE_MOTION:
		{
			float x = AMotionEvent_getX(inputEvent, 0);
			float y = AMotionEvent_getY(inputEvent, 0);
			Log("[INPUT] TOUCH @ %f, %f", x, y);

			int width = ANativeWindow_getWidth(application->window);
			int height = ANativeWindow_getHeight(application->window);
			if(graphicInitialized)
			{
			glClearColor(x / width, y / height, (x + y) / (width + height), 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			eglSwapBuffers(tempData->display, tempData->surface);
			}
		}
			return 1;
		default:
			break;
		}

		return 0;
	}


	
	static void createGraphicsContext(android_app* application)
	{
		bool paskafix;
		ANativeWindow* windowHandle = application->window;
		//struct data* tempData = (struct data*)application->userData;
		Impl *tempData = static_cast<Impl*>(application->userData);
		const EGLint configAttributes[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_NONE
		};
		const EGLint surfaceAttributes[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
		};
		tempData->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		Log("%s %i", "DISPLAY", tempData->display != EGL_NO_DISPLAY);
		//assert(tempData->display != EGL_NO_DISPLAY);
		paskafix = eglInitialize(tempData->display, nullptr, nullptr);
		Log("%s %i", "INITIALIZE", paskafix);
		//assert(paskafix);
		EGLConfig config;
		EGLint configCount;
		paskafix = eglChooseConfig(tempData->display, configAttributes, &config, 1, &configCount);
		Log("%s %i", "CHOOSECONFIG", paskafix);
		//assert(paskafix);
		EGLint format;
		paskafix = eglGetConfigAttrib(tempData->display, config, EGL_NATIVE_VISUAL_ID, &format);
		Log("%s %i", "GETCONFIGATTRIB", paskafix);
		//assert(paskafix);
		ANativeWindow_setBuffersGeometry(windowHandle, 0, 0, format);

		tempData->surface = eglCreateWindowSurface(tempData->display, config, static_cast<EGLNativeWindowType>(windowHandle), nullptr);
		Log("%s %i", "createWindowsurface", tempData->surface != EGL_NO_SURFACE);
		//assert(tempData->surface != EGL_NO_SURFACE);
		tempData->context = eglCreateContext(tempData->display, config, nullptr, surfaceAttributes);
		Log("%s %i", "createContext", tempData->context != EGL_NO_CONTEXT);
		//assert(tempData->context != EGL_NO_CONTEXT);
		paskafix = eglMakeCurrent(tempData->display, tempData->surface, tempData->surface, tempData->context);
		Log("%s %i", "makeCurrent", paskafix);
		//assert(paskafix);
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Log("%s", "Testing createContext1", paskafix);
		eglSwapBuffers(tempData->display, tempData->surface);
		Log("%s", "Testing createContext2", paskafix);
		graphicInitialized = true;
		LoadShaders();
	}
		static void LoadShaders()
	{
		//ResourceMan
	}
	static void destroyGraphicsContext(android_app* application)
	{
		//struct data* tempData = (struct data*)application->userData;
		Impl *tempData = static_cast<Impl*>(application->userData);
		eglMakeCurrent(tempData->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(tempData->display, tempData->context);
		eglDestroySurface(tempData->display, tempData->surface);
		eglTerminate(tempData->display);
	}
}
;
Application::Application() : _impl(new Impl())
{
}

void Application::Update()
{
	_impl->Update();
}
void Application::Log(const char *format,...)
{
	va_list arg;

	va_start(arg, format);
	
	_impl->Log(format, arg);
	va_end(arg);
}
Application::~Application()
{
	delete this->_impl;
}
void android_main(android_app* application)
{
	Application a;
	ResourceManager::Initialize(application);
	std::string stringtest;
	ResourceManager::readFile("hello.txt", stringtest);
	a.Log("%s",stringtest.data());
	a._impl->Initialize(application);
	while (true)
	{
		a.Update();
	}

		//TODO Update and draw
	}
//#endif