
#include "Application.h"
#include "ResourceManager.h"

void android_main(android_app* application)
{
	Application app;

	std::string out;
	ResourceManager::readFile("hello.txt", application, out);
	LOG("[TEST] '%s'", out.data());

	app._impl->Initialize(application);

	while (true)
	{
		app.Update();
	}
	//TODO Update and draw
}
