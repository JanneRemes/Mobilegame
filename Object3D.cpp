#include "Object3D.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   
Object3D::Object3D(android_app *application, const char *objectFileName, const char *imageFileName)
{
y = 0.0f;
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
	goingRight = false;
	goingUp = true;
	yChange = 3.0f;
	  srand (time(NULL));
	  gameOver = false;
}
	void Object3D::Update(float y)
	{
		if(goingUp)
			y+=yChange;
		else
			y-= yChange;
		if(goingRight)
			x+=3;
		else 
			x-=3;
			

		if(y < -400)
		{
			goingUp = true;
			yChange = rand() % 5;
		}
		else if(y > 400)
		{
			goingUp = false;
			yChange = rand() % 5;
		}
					if(gameOver)
			return;
		if(x < -280.0f)
		{
		if(this->y >y - 260.0f && this->y < y + 260.0f)
			goingRight = true;
			else
			gameOver = true;
		}
		else if(x > 100.0f)
		{
			if(this->y >y - 260.0f && this->y < y + 260.0f)
			goingRight = false;
			else
			gameOver = true;
		}
	}
Object3D::~Object3D()
{
}