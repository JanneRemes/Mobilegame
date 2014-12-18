#include "ObjectLoader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "NativeSample", __VA_ARGS__);
#include "ResourceManager.h"
#include <string>
 bool ObjectLoader::loadObject(const char *filename)
{
std::string file;
LOG("[THIS FAR]");
	ResourceManager::readFile(filename, file);
	//LOG("[OBJDATA]%s",file.c_str());
	 while (1){
		std::string lineHeader;
		// char lineHeader[128];
		 // read the first word of the line
		 int res = sscanf(file.c_str(), "%s", lineHeader.data());
		 lineHeader = std::string(lineHeader.c_str());
		// LOG("[RES]%d",res);
		 if (res == EOF)
		 {
			 break; // EOF = End Of File. Quit the loop.
			 }

			// LOG("[LINE]%s",lineHeader.c_str());
			 std::size_t found = file.find(lineHeader);
			// LOG("[FOUND]%d",found);
			 if (found!=std::string::npos)
			 {
			// LOG("[FOUNDY]");
			 size_t size = found + lineHeader.size();
			 file = file.substr(size,std::string::npos);
			//  LOG("[CALCULATED]%d",size);
			//  LOG("[SIZEOFSTRING]%d",lineHeader.size());
			 }
			 
		 if (strcmp(lineHeader.c_str(), "v") == 0){
		  glm::vec3 vertex;
		 // LOG("[V]");
		  sscanf(file.c_str(), "%f %f %f", &vertex.x, &vertex.z, &vertex.y);
		 // LOG("[VERTEX]%f %f %f",vertex.x,vertex.y,vertex.z);
		  temp_vertices.push_back(vertex.x);
			temp_vertices.push_back(vertex.y);
			temp_vertices.push_back(vertex.z);
		 /*
			 glm::vec3 vertex;
			 fscanf(file, "%f %f %f\n", &vertex.x, &vertex.z, &vertex.y);
			 std::cout << "VERTEX: " << vertex.x<<"," << vertex.y << "," << vertex.z << std::endl;
			 vertex.x /= 50.0f;
			 vertex.y /= 50.0f;
			 vertex.z /= 50.0f;
			 std::cout << "VERTEX: " << vertex.x << "," << vertex.y << "," << vertex.z << std::endl;
			 temp_vertices.push_back(vertex.x);
			 temp_vertices.push_back(vertex.y);
			 temp_vertices.push_back(vertex.z);
			 */
		 }
		 else if (strcmp(lineHeader.c_str(), "vt") == 0){
		  //LOG("[VT]");
		   glm::vec2 uv;
		   sscanf(file.c_str(), "%f %f\n", &uv.x, &uv.y);
		  // LOG("[UV]%f %f",uv.x,uv.y);
		    temp_uvs.push_back(uv);
		 /*
			 glm::vec2 uv;
			 fscanf(file, "%f %f\n", &uv.x, &uv.y);
		 std::cout <<"UV: "<< uv.x<<"," << uv.y << std::endl;
			 temp_uvs.push_back(uv);
			 */
		 }

		 else if (strcmp(lineHeader.c_str(), "f") == 0){
		 // LOG("[F]");
		  unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			 int matches = sscanf(file.c_str(), "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0],  &vertexIndex[1], &uvIndex[1],  &vertexIndex[2], &uvIndex[2]);
			 if (matches != 6){
				  LOG("File can't be read by our simple parser : ( Try exporting with other options\n");
				 return false;
			 }
			 for (int i = 0; i < 3; i++)
			 {
				 vertexIndex[i]--;
				 uvIndex[i]--;
			 }
			 //LOG("[VERTEX]%d %d %d",vertexIndex[0],vertexIndex[1],vertexIndex[2]);
			// LOG("[VERTEX]%d %d %d",uvIndex[0],uvIndex[1],uvIndex[2]);
			 vertexIndices.push_back(vertexIndex[0]);
			 vertexIndices.push_back(vertexIndex[1]);
			 vertexIndices.push_back(vertexIndex[2]);
			 vertexIndices2.push_back(vertexIndex[0]);
			 vertexIndices2.push_back(vertexIndex[1]);
			 vertexIndices2.push_back(vertexIndex[2]);
			 uvIndices.push_back(uvIndex[0]);
			 uvIndices.push_back(uvIndex[1]);
			 uvIndices.push_back(uvIndex[2]);
		  
		 /*
			 std::string vertex1, vertex2, vertex3;
			 unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			 int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0],  &vertexIndex[1], &uvIndex[1],  &vertexIndex[2], &uvIndex[2]);
			 if (matches != 6){
				 printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				 return false;
			 }
			 std::cout << "VERTEX INDICES: " << vertexIndex[0] << "," << vertexIndex[1] << "," << vertexIndex[2] << std::endl;
			 std::cout << "UV INDICES: " << uvIndex[0] << "," << uvIndex[1] << "," << uvIndex[2] << std::endl;
			 vertexIndices.push_back(vertexIndex[0]);
			 vertexIndices.push_back(vertexIndex[1]);
			 vertexIndices.push_back(vertexIndex[2]);
			 vertexIndices2.push_back(vertexIndex[0]);
			 vertexIndices2.push_back(vertexIndex[1]);
			 vertexIndices2.push_back(vertexIndex[2]);
			 uvIndices.push_back(uvIndex[0]);
			 uvIndices.push_back(uvIndex[1]);
			 uvIndices.push_back(uvIndex[2]);
			 */

		 }
	 }
	 
	 
	 //fclose(file);
	 LOG("[VERTEX_SIZE]%d",temp_vertices.size());
	 LOG("[UV_SIZE]%d",temp_uvs.size());
	 LOG("[VERTEX_INDICES_SIZE]%d",vertexIndices.size());
	 LOG("[UV_INDICES_SIZE]%d",uvIndices.size());
	 for (int i = 0; i <vertexIndices.size(); i++)
	 {
		 final_data.push_back(temp_vertices.at(vertexIndices[i] * 3));
		 final_data.push_back(temp_vertices.at(vertexIndices[i] * 3 + 1));
		 final_data.push_back(temp_vertices.at(vertexIndices[i] * 3 + 2));
		 final_data.push_back(0.0f);//COLOR
		 final_data.push_back(0.0f);//COLOR
		 final_data.push_back(0.0f);//COLOR
		 final_data.push_back(temp_uvs[uvIndices[i]].x);//UV
		 final_data.push_back(temp_uvs[uvIndices[i]].y);//UV
		 /*
		 final_data.push_back(temp_vertices.at(i));
		 final_data.push_back(temp_vertices.at(i+1));
		 final_data.push_back(temp_vertices.at(i+2));
		 final_data.push_back(0.0f);//COLOR
		 final_data.push_back(0.0f);//COLOR
		 final_data.push_back(0.0f);//COLOR
		 final_data.push_back(temp_uvs.at(0).x);//UV
		 final_data.push_back(temp_uvs.at(0).y);//UV
		 */
	 }
	 LOG("[SIZEOFDATA]%d",final_data.size());
	 
	 	 int oldSize = vertexIndices.size();
	 for (int i = 0; i < oldSize; i++)
	 {
		 vertexIndices2[i] = i;
	 }
	 /*
	 std::ifstream myFile;
	 myFile.open(filename);
	 if (myFile.is_open())
	 {
		 char buf[256]; //create buffer to read line
		 int i = 0;
		 while (!myFile.eof())//while we are not at the end of the file.
		 {
			 i++;
			 myFile.getline(buf, 256);
			 std::cout << buf << std::endl;
			 if (strcmp(buf, "vt") == 0)
			 {
				 continue;
			 }
			 glm::vec3 vertex;
			 std::istringstream ss(buf);
			 switch (buf[0])
			 {

			 case 'v':
				 float f;
				 if (!(ss >> f))
				 {
					 std::cout << f << std::endl;
					 // error: didn't convert to a float
				 }
				 //scanf(buf,"%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				 //fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				// std::cout << vertex.x << "," << vertex.y << "," << vertex.z << i << std::endl;
				 //temp_vertices.push_back(vertex);
				 break;
			 case 'f':
				 break;
			 default:
				 break;
			 }
		 }

	 }*/
	 /*
	int i = 0;
	while (1){
		i++;
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "#") == 0){
			continue;
		}
		if (strcmp(lineHeader, "vt") == 0)
		{
			std::cout  << i << std::endl;
			continue;
		}
		glm::vec3 vertex;
		switch (lineHeader[0])
		{
		case 'v':
			
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			std::cout << vertex.x << "," << vertex.y << "," << vertex.z <<i<< std::endl;
			temp_vertices.push_back(vertex);
			break;
		case 'f':
			break;
		default:
			break;
		}
	*/
		
		/*
			if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			std::cout << vertex.x << "," << vertex.y << "," << vertex.z << std::endl;
			temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0){
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "f") == 0){
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9){
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

			}
			*/
	

	return true;

}
