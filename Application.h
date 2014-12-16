#pragma once
#include <stdio.h>
#include <stdarg.h>
class Application
{
public:
	Application();
	void Log(const char*format,...);
	~Application();
	void Update();
	class Impl;
	Impl* _impl;
private:

};

