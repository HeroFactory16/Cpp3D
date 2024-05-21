#include "VertexShader.h"

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

VertexShader::VertexShader() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    CompilationWorks();
}

void VertexShader::CompilationWorks() {
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "VERTEX SHADER : COMPILATION FAILED: \n" << infolog << std::endl;
    }
    else {
        std::cout << "COMPILATION DONE" << std::endl;
    }
}

unsigned int VertexShader::GetVertexShader() {
    return vertexShader;
}
