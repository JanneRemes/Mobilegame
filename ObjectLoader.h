#pragma once
#include <vector>
#include "glm\glm.hpp"
#include <GLES2/gl2.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include <string>
class ObjectLoader
{
public:
	ObjectLoader(android_app *application){this->application = application;}
	ObjectLoader(){}
	std::vector< unsigned int > vertexIndices, uvIndices;
	std::vector< GLint > vertexIndices2;
	std::vector< glm::vec2 > temp_uvs;
	std::vector<GLfloat> temp_vertices;
	bool loadObject(const char *filename);
	std::vector<GLfloat> final_data;
	std::vector<GLint> *getINDEX()
	{
		return &vertexIndices2;
	}
	std::vector<GLfloat> *getFinalVertex()
	{
		return &final_data;
	}
	private:
	android_app *application;
};

