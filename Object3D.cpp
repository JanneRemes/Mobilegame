#include "Object3D.h"
Object3D::Object3D(android_app *application, const char *objectFileName, const char *imageFileName)
{
this->application = application;
this->fileName = fileName;
object = ObjectLoader(application);
	object.loadObject(objectFileName);
		glGenTextures(1, &_texture);//generates texture
			std::vector<unsigned char> out;
	ResourceManager::loadImage(out,imageFileName);
		glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ResourceManager::width, ResourceManager::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out.at(0));



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,0);
}

Object3D::~Object3D()
{
}