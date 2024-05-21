#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class SubMesh {
public:
	std::vector<glm::vec3> vertis;
	std::vector<glm::vec3> normals;
	std::vector < glm::vec3> uv;

	std::vector<glm::vec3> global;
};