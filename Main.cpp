#include <android/asset_manager.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>   //rand
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__);

EGLDisplay display;
EGLSurface surface;
EGLContext context;
static int processInput(struct android_app* application,AInputEvent* inputEvent);
static void processCommand(android_app* application, int command);
static void createGraphicsContext(ANativeWindow* windowHandle);
static void destroyGraphicsContext();

void android_main(android_app* application)
{
srand(time(NULL));
/*
	AAssetManager* assetManager = application->activity->assetManager;
	AAsset* asset = AAssetManager_open(assetManager,"hello.txt",AASSET_MODE_UNKNOWN);
    char buffer[250];
    AAsset_read (asset,buffer,250);
	int size = AAsset_getLength(asset);
	if(size < 250)
	buffer[size] = 0;
    LOG("value: %s", buffer);
    AAsset_close(asset);
	*/
	application->onAppCmd = processCommand;
	application->onInputEvent = processInput;
	bool isRunning = true;
	android_poll_source* eventSource;

	while (isRunning)
	{
		while (ALooper_pollAll(0, nullptr, nullptr, reinterpret_cast<void**>(&eventSource)) >= 0)
		{
			if (eventSource != nullptr)
				eventSource->process(application, eventSource);

			if (application->destroyRequested != 0)
			{
				isRunning = false;
				break;
			}
		}

		//TODO Update and draw
	}
}

static void processCommand(android_app* application, int command)
{
	switch (command)
	{
	case APP_CMD_INIT_WINDOW:
		createGraphicsContext(application->window);
		break;

	case APP_CMD_TERM_WINDOW:
		destroyGraphicsContext();
		break;

	case APP_CMD_RESUME:
		LOG("RESUME");
		break;

	case APP_CMD_PAUSE:
		LOG("PAUSE");
		break;

	default:
		break;
	}
}
int processInput(struct android_app* application,AInputEvent* inputEvent)
{
switch(AInputEvent_getType(inputEvent))
{
	case AINPUT_EVENT_TYPE_MOTION:
		{
		float x = AMotionEvent_getX(inputEvent,0);
		float y = AMotionEvent_getY(inputEvent, 0);
		LOG("[INPUT] TOUCH @ %f, %f",x,y);

		int width =  ANativeWindow_getWidth(application->window);
		int height = ANativeWindow_getHeight(application->window);
				//float l = (rand() % 50) / 50.0f;
		//float u = (rand() % 50) / 50.0f;
	//	float o = (rand() % 50) / 50.0f;
		//LOG("%f",l);
        glClearColor(x/width,y/height,(x+y)/(width+height), 1.0f);
		//int height = app->window->height;
		glClear(GL_COLOR_BUFFER_BIT);
		eglSwapBuffers(display, surface);
		}
		return 1;
	default:
		break;
}

	return 0;
}
static void createGraphicsContext(ANativeWindow* windowHandle)
{
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

	 display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(display, nullptr, nullptr);

	EGLConfig config;
	EGLint configCount;

	eglChooseConfig(display, configAttributes, &config, 1, &configCount);

	EGLint format;
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(windowHandle, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, static_cast<EGLNativeWindowType>(windowHandle), nullptr);
	EGLContext context = eglCreateContext(display, config, nullptr, surfaceAttributes);
	eglMakeCurrent(display, surface, surface, context);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	eglSwapBuffers(display, surface);
} 

static void destroyGraphicsContext()
{
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(display, context);
	eglDestroySurface(display, surface);
	eglTerminate(display);
}
