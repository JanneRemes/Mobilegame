#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include "lodepng.h"
#include <vector>
class ResourceManager
{
public:

	class Impl;
	static Impl* _impl;
	static void Initialize(android_app* app);
	static void readFile(const char* pathToFile, std::string& out);
	static android_app* application;
	static void loadImage(std::vector<unsigned char>& out,const char *filename);
	static unsigned height, width;
private:
};

