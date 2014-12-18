#include "ResourceManager.h"
#include <android/log.h>

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__);
android_app* ResourceManager::application;
unsigned ResourceManager::height;
unsigned ResourceManager::width;
class ResourceManager::Impl
{
	
public:
	void readFile(const char* pathToFile, std::string& out)
	{
	AAssetManager* assetManager = application->activity->assetManager;
	AAsset* asset = AAssetManager_open(assetManager, pathToFile, AASSET_MODE_UNKNOWN);
	LOG("PATHTOFILE: %s",pathToFile);
	const size_t length = AAsset_getLength(asset);
	LOG("[DEBUG] AssetLength = %d", length);
	std::vector<char> buffer(length, 0);
		
	AAsset_read(asset, buffer.data(), buffer.size());
	AAsset_close(asset);

	out.assign(buffer.begin(), buffer.end());
	}
};
ResourceManager::Impl* ResourceManager::_impl;
//static bool initialized = false;
void ResourceManager::Initialize(android_app* app)
{
LOG("HERE");
	_impl = new Impl();
	ResourceManager::application = app;
	LOG("HERE ASWELL");
	//initialized = true;
}
void ResourceManager::readFile(const char* pathToFile, std::string& out)
{
	_impl->readFile(pathToFile,out);
}

void ResourceManager::loadImage(std::vector<unsigned char>& out,const char *filename)
{
std::string instring = std::string();
ResourceManager::readFile(filename,instring);
std::vector<unsigned char> data(instring.begin(), instring.end());
unsigned error = lodepng::decode(out, width, height,data);


int widthInChars = width * 4;
unsigned char* imagePtr = &out[0];
unsigned char* top = nullptr;
unsigned char* bottom = nullptr;
unsigned char temp = 0;

for( int h = 0; h < width / 2; h++ )
{
	top = imagePtr + h * widthInChars;
	bottom = imagePtr + (height - h - 1) * widthInChars;
	for( int w = 0; w < widthInChars; w++)
	{
		temp = *top;
		*top = *bottom;
		*bottom = temp;
		top++;
		bottom++;
	}
}



}
/*
void loadImage(

int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "test.png";
  
  //load and decode
  std::vector<unsigned char> buffer, image;
  loadFile(buffer, filename);
  unsigned long w, h;
  int error = decodePNG(image, w, h, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());
  
  //if there's an error, display it
  if(error != 0) std::cout << "error: " << error << std::endl;
  
  //the pixels are now in the vector "image", use it as texture, draw it, ...
  
  if(image.size() > 4) std::cout << "width: " << w << " height: " << h << " first pixel: " << std::hex << int(image[0]) << int(image[1]) << int(image[2]) << int(image[3]) << std::endl;
}

/*
  //this is test code, it displays the pixels of a 1 bit PNG. To use it, set the flag convert_to_rgba32 to false and load a 1-bit PNG image with a small size (so that its ASCII representation can fit in a console window)
  for(int y = 0; y < h; y++)
  {
    for(int x = 0; x < w; x++)
    {
      int i = y * h + x;
      std::cout << (((image[i/8] >> (7-i%8)) & 1) ? '.' : '#');
    }
    std::cout << std::endl;
  }
*/

