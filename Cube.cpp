#include "Cube.h"

Cube::Cube(std::vector<glm::vec3> vertis) {
	vertisAndUV = vertis;
	SetVVector(&subMesh);
	SetNormal(&subMesh);
	SetUV(&subMesh);
	SetGlobal(&subMesh);
}

Cube::Cube() : _vertis {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.f, 0.f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.f, 0.f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.f, 1.f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.f, 1.f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.f, 1.f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.f, 0.f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.f, 1.f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.f, 0.f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.f, 1.f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.f, 1.f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.f, 0.f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.f, 1.f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.f, 1.f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.f, 1.f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.f, 0.f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.f, 1.f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.f, 1.f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.f, 1.f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
    }{

}

void Cube::SetVVector(SubMesh* subMesh) {
	for (int i = 0; i < vertisAndUV.size(); i += 2) {
		if (i % 2 == 0) {
			subMesh->vertis.push_back(vertisAndUV[i]);
		}
	}
}

void Cube::SetNormal(SubMesh* subMesh) {
	for (int i = 0; i < subMesh->vertis.size(); i += 3) {

		glm::vec3 normU = subMesh->vertis[i + 1] - subMesh->vertis[i];
		glm::vec3 normV = subMesh->vertis[i + 2] - subMesh->vertis[i];

		glm::vec3 normal = glm::cross(normU, normV);
		subMesh->normals.push_back(normal);
		subMesh->normals.push_back(normal);
		subMesh->normals.push_back(normal);
	}
}

void Cube::SetUV(SubMesh* subMesh) {
	for (int i = 1; i < vertisAndUV.size(); i += 2) {
		if (i % 2 == 1) {
			subMesh->uv.push_back(vertisAndUV[i]);
		}
	}
}

void Cube::SetGlobal(SubMesh* subMesh) {
	for (int i = 0; i < subMesh->normals.size(); i++) {
		subMesh->global.push_back(subMesh->vertis[i]);
		subMesh->global.push_back(subMesh->uv[i]);
		subMesh->global.push_back(subMesh->normals[i]);
	}
}