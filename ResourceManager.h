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
	static void Initialize(android_app* app);
	static void readFile(const char* pathToFile, std::string& out);
	static android_app* application;
private:
};

