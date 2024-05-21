#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "SubMesh.h"

class Object {
public:
	std::vector<std::string> lines;
	std::vector<glm::vec3> vVector;
	std::vector<unsigned int> fVector;
	SubMesh subMesh;

	Object(const char* path);
	std::vector<glm::vec3> GetVertexVector();
	std::vector<unsigned int> GetFVector();
	void SortVVector(SubMesh* subMesh);
	void SetNormal(SubMesh* subMesh);
	void SetGlobal(SubMesh* subMesh);

private:
	std::vector<std::string> GetFileContentByLine(const char* path);
};