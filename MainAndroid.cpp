#if defined(ANRDROID)
#include "Application.h"
void android_main(android_app* application)
{
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
#endif