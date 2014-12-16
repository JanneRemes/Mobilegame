#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
class ResourceManager
{
public:

	class Impl;
	static Impl* _impl;
	static void Initialize();
	static void readFile(const char* pathToFile, android_app* application, std::string& out);
private:
};

