#include "ResourceManager.h"
#include <android/log.h>
#include <vector>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__);
class ResourceManager::Impl
{
	
public:
	void readFile(const char* pathToFile, android_app* application, std::string& out)
	{
	AAssetManager* assetManager = application->activity->assetManager;
	AAsset* asset = AAssetManager_open(assetManager, pathToFile, AASSET_MODE_UNKNOWN);

	const size_t length = AAsset_getLength(asset);
	LOG("[DEBUG] AssetLength = %d", length);
	std::vector<char> buffer(length, 0);
		
	AAsset_read(asset, buffer.data(), buffer.size() - 1);
	AAsset_close(asset);

	out.assign(buffer.begin(), buffer.end());
	}
};
ResourceManager::Impl* ResourceManager::_impl;
//static bool initialized = false;
void ResourceManager::Initialize()
{
	_impl = new Impl();
	//initialized = true;
}
void ResourceManager::readFile(const char* pathToFile, android_app* application, std::string& out)
{
	_impl->readFile(pathToFile,application,out);
}