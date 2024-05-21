#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexShader {
	const char* vertexShaderSource;
	unsigned int vertexShader;
	int success;
	char infolog[512];

public:
	VertexShader();
	void CompilationWorks();
	unsigned int GetVertexShader();
};