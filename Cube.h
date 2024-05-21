#pragma once
#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "SubMesh.h"

class Cube {
public:
	SubMesh subMesh;
	std::vector<glm::vec3> vertisAndUV;
    float _vertis[36*8];

	Cube(std::vector<glm::vec3> vertisAndUV);
	Cube();
	void SetVVector(SubMesh* subMesh);
	void SetNormal(SubMesh* subMesh);
	void SetUV(SubMesh* subMesh);
	void SetGlobal(SubMesh* subMesh);
};