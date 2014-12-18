//#if defined(ANDROID)
#include "Application.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>
#include "ResourceManager.h"
#define GLM_FORCE_RADIANS
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include <vector>
#include "ObjectLoader.h"
#include "Object3D.h"
static bool graphicInitialized;
static GLuint _program;
static GLint _positionIndex;
static GLint _colorIndex;
static GLint _textureIndex;
static GLuint buffers[2];
static glm::mat4 worldTransform;
static GLint worldIndex;
static float rotation = 90.0f;
static GLint alphaIndex;
static GLint viewIndex;
static Object3D *l;
static Object3D *l2;
static Object3D *pallo;
static std::vector<GLfloat> _vertexBufferInput = 
{
		//vasen ala
		-0.5f, 0.0f, -0.5f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f,


		//oikea ala
		0.5f, 0.0f, -0.5f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f,

		//oikea ylä
		0.5f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f,
		//vasen ylä
		-0.5f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f,

		//vasen ala
		-0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		-0.5f, 0.0f,

		//vasen ylä
		-0.5f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		-0.5f, 1.0f,
		//oikea ylä
		0.5f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.5f, 1.0f,

		//oikea ala
		0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.5f, 0.0f
	};
	static std::vector<GLuint> _indexBufferInput = {
		0u, 1u, 2u,
		2u, 3u, 0u,
		4u, 5u, 6u,
		6u, 7u, 4u
		/*0u, 1u, 4u,
		1u, 2u, 4u,
		2u,3u,4u,
		3u,0u,4u*/

	};
		static bool speeding = true;
class Application::Impl
{

public:
		//from previos






	//end of previous
		//from rendering context

	GLuint vertexShader;
	GLuint fragmentShader;
	
	
	
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
	static void DrawObject(Object3D *objectPointer)
	{
	
	worldTransform = glm::translate(glm::vec3(objectPointer->x/10.0f, objectPointer->y/ 10.0f, 0.0f)) *glm::rotate(rotation* 0.0174532925f, glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(glm::vec3(1.0f, -1.0f, 1.0f));
	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));
	
	glBindTexture(GL_TEXTURE_2D, objectPointer->getTextureID());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * ObjectLoader::getVERTEX()->size(), &ObjectLoader::getVERTEX()->at(0), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * objectPointer->getFinalVertex()->size(), &objectPointer->getFinalVertex()->at(0), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * objectPointer->getINDEX()->size(), &objectPointer->getINDEX()->at(0), GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, objectPointer->getINDEX()->size(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
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

		//glStencilFunc(GL_GEQUAL, 1, 255);
		//glScissor(100, 100, 600, 400);
		if(!graphicInitialized)
		return;
			pallo->Update(l->y);
		glUseProgram(_program);
		glm::mat4 worldTransform = /*glm::translate(glm::vec3(0.0f + test, 0.0f, 0.0f)) * */glm::rotate(rotation* 0.0174532925f, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(1,1, 1));
		glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));
		glm::mat4 viewTransform = glm::translate(glm::vec3(0.0f, -0.5f, -100.0f));
		glUniformMatrix4fv(viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&viewTransform));



		glUseProgram(0u);
		Render(application);

	}
	static void Render(android_app* application)
	{
	glFlush();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glUseProgram(_program);
	
	//OBJ
	//worldTransform = glm::mat4();
	/*
	glBindBuffer(GL_ARRAY_BUFFER, myObjectBuffer);
	glVertexAttribPointer(_positionIndex, 3, GL_FLOAT, GL_FALSE,12, reinterpret_cast<GLvoid*>(0));

	glDrawElements(GL_TRIANGLES, ObjectLoader::getVERTEX().size(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));
	*/
	//END OF OBJ
		glUniform1f(alphaIndex, 1.0f);
	DrawObject(l2);
	DrawObject(l);
	DrawObject(pallo);
	//END OF OBJ
	/*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexBufferInput.size(), &_vertexBufferInput.at(0), GL_STATIC_DRAW);//sizeof(_vertexBufferInput) might return a value that is not always correct...
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indexBufferInput.size(), &_indexBufferInput.at(0), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);//syvyyspuskuri läpi niin korvataan arvot
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);
	//glBindTexture(rendContext.getProgramIndex(), _texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Lattia
	worldTransform = glm::rotate(rotation* 0.0174532925f, glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));
	glUniform1f(alphaIndex, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));

	//seinä
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(24));


	glUniform1f(alphaIndex, -0.5f);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);
	worldTransform = glm::rotate(rotation* 0.0174532925f, glm::vec3(0.0f, 0.0f, 1.0f))*glm::scale(glm::vec3(1.0f, -1.0f, 1.0f));
	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));
	//seinä reflection

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(24));
	//glBindTexture(_program, 0u);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_STENCIL_TEST);
	*/
	glUseProgram(0);
	
	Impl *tempData = static_cast<Impl*>(application->userData);
	eglSwapBuffers(tempData->display, tempData->surface);
	}
	

	static void processCommand(android_app* application, int command)
	{
		switch (command)
		{
			
		case APP_CMD_INIT_WINDOW:
			createGraphicsContext(application);
			break;
			
		case APP_CMD_TERM_WINDOW:
			destroyGraphicsContext(application);
			graphicInitialized = false;
			break;
			
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
			l->y = -y + 350;
			l2->y = -y + 350;
			int width = ANativeWindow_getWidth(application->window);
			int height = ANativeWindow_getHeight(application->window);
			if(graphicInitialized)
			{
			//glClearColor(x / width, y / height, (x + y) / (width + height), 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);
			//eglSwapBuffers(tempData->display, tempData->surface);
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
		LoadShaders(application);
			l = new Object3D(application,"box1.obj","box1.png");
			l->x = -400.0f;
	l2 = new Object3D(application, "box1.obj","box1.png");
	l2->x = 200.0f;
	pallo = new Object3D(application,"box2.obj","box2.png");
	pallo->x = -100.0f;
	pallo->y = 0.0f;
	}
		static void LoadShaders(android_app* application)
	{
		//ResourceMan
		_program = glCreateProgram();
			Log("Program created, value: %d",_program);
		std::string vertexSource;
		std::string fragmentSource;
		ResourceManager::readFile("vertexSource.txt", vertexSource);
		ResourceManager::readFile("fragmentSource.txt", fragmentSource);
		//Log("[VERTEX]%s",vertexSource.data());
		//Log("[FRAGMENT]%s",fragmentSource.data());
		//VERTEX SOURCE
		const GLchar *vertexFormatted = (GLchar*)vertexSource.data();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexFormatted, nullptr);
		glCompileShader(vertexShader);

		GLint compileResult;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileResult);
		Log("[VERTEXCOMPILE]%d", compileResult == GL_TRUE);

		glAttachShader(_program, vertexShader);
		//FRAGMENT SOURCE
		const GLchar *fragmentFormatted = (GLchar*)fragmentSource.data();
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentFormatted, nullptr);
		glCompileShader(fragmentShader);
		
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileResult);
		Log("[FRAGMENTCOMPILE]%d", compileResult == GL_TRUE);

		glAttachShader(_program, fragmentShader);
		
		//LINK PROGRAM
		
		glLinkProgram(_program);

		glGetProgramiv(_program, GL_LINK_STATUS, &compileResult);
		Log("[PROGRAM LINK]%d", compileResult == GL_TRUE);
		setLocations(application);
	}
	static void setLocations(android_app* application)
	{
	
	//activate attribute arrays
	_positionIndex = glGetAttribLocation(_program, "attrPosition");
	Log("SO FAR");
	Log("[POSITIONINDEX]%d",(_positionIndex >= 0));
	glEnableVertexAttribArray(_positionIndex);

	_colorIndex = glGetAttribLocation(_program, "attrColor");
	Log("[COLORINDEX]%d",_colorIndex >= 0);
	glEnableVertexAttribArray(_colorIndex);

	_textureIndex = glGetAttribLocation(_program, "attrTexCoord");
	Log("[TEXTUREINDEX]%d",_textureIndex >= 0);
	glEnableVertexAttribArray(_textureIndex);


	const GLint _samplerLocation = glGetUniformLocation(_program, "myTexture");
	Log("[SAMPLERINDEX]%d",_samplerLocation >= 0);

	const GLint _projectionLocation = glGetUniformLocation(_program, "unifProjection");
	Log("[PROJECTIONINDEX]%d",_projectionLocation != -1);

	 worldIndex = glGetUniformLocation(_program, "unifWorld");
	Log("[POSITIONINDEX]%d",worldIndex != -1);

	viewIndex = glGetUniformLocation(_program, "unifView");
	Log("[VIEWINDEX]%d",viewIndex != -1);
	alphaIndex = glGetUniformLocation(_program, "unifAlpha");
	Log("[ALPHAINDEX]%d",alphaIndex != -1);
	
	
	//TEXTURE


	//_texture = glGetUniformLocation(_program, "myTexture"); 
	//assert(_texture >= 0);

	
	

	
	
	
	
	//BUFFERS
	
		glGenBuffers(2, buffers);
	
	

		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, _vertexBufferInput.size() * sizeof(GLfloat), &_vertexBufferInput.at(0), GL_STATIC_DRAW);//sizeof(_vertexBufferInput) might return a value that is not always correct...
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Log("[ARRAYBUFFER]");




		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexBufferInput.size()* sizeof(GLfloat), &_indexBufferInput.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		Log("[INDEXBUFFER]");
		
		
		
		
		
	//OTHER STUFF
	
	int width = ANativeWindow_getWidth(application->window);
	int height = ANativeWindow_getHeight(application->window);
	glUseProgram(_program);
	//lUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&_projection));
	glm::mat4 projectionTransform = glm::perspective(60.0f * 0.0174532925f, static_cast<float>(width)//res X
		/ height // res y
		, 0.01f, 1000.0f);
	glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, reinterpret_cast<float*>(&projectionTransform));

	worldTransform = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(40.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(worldIndex, 1, GL_FALSE, reinterpret_cast<float*>(&worldTransform));

	glm::mat4 viewTransform = glm::translate(glm::vec3(0.0f, 0.0f, -100.0f));
	glUniformMatrix4fv(viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&viewTransform));




	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

	glVertexAttribPointer(_positionIndex, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<GLvoid*>(0));

	glVertexAttribPointer(_colorIndex, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<GLvoid*>(12));

	glVertexAttribPointer(_textureIndex, 2, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<GLvoid*>(24));

	glUseProgram(0u);




	glClearColor(0.2f, 0.4f, 0.8f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

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

	a._impl->Initialize(application);
	

	//a.Log("[VERTEXSIZE]%d",l.getINDEX()->size());
	while (true)
	{
		a.Update();
	}

		//TODO Update and draw
	}
//#endif