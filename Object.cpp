#include "Object.h"
#include <fstream>
#include <sstream>

Object::Object(const char* path) {
	std::vector<std::string> objContent;

	objContent = GetFileContentByLine(path);
}

std::vector<std::string> Object::GetFileContentByLine(const char* path) {
	std::vector<std::string> fileContent;
	try {
		std::ifstream objFile;
		objFile.open(path);
		for (std::string line; std::getline(objFile, line);) {
			std::stringstream lineStream(line);
			std::string token;
			lineStream >> token;
			if (token == "v") {
				lineStream >> token;
				float x = std::stof(token);
				lineStream >> token;
				float y = std::stof(token);
				lineStream >> token;
				float z = std::stof(token);
				glm::vec3 vertis = glm::vec3(x, y, z);
				vVector.push_back(vertis);
			}

			if (token == "f") {
				lineStream >> token;
				fVector.push_back(std::stoi(token) - 1);
				lineStream >> token;
				fVector.push_back(std::stoi(token) - 1);
				lineStream >> token;
				fVector.push_back(std::stoi(token) - 1);
			}
			fileContent.push_back(line);
		}
		objFile.close();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR : File can't be read" << e.what() << std::endl;
	}

	lines = fileContent;

	SortVVector(&subMesh);
	SetNormal(&subMesh);
	SetGlobal(&subMesh);

	return fileContent;
}

std::vector<glm::vec3> Object::GetVertexVector() {
	return vVector;
}

std::vector<unsigned int> Object::GetFVector() {
	return fVector;
}

void Object::SortVVector(SubMesh* subMesh) {
	for (int i = 0; i < fVector.size(); ++i) {
		subMesh->vertis.push_back(vVector[fVector[i]]);
	}
}

void Object::SetNormal(SubMesh* subMesh) {
	for (int i = 0; i < subMesh->vertis.size(); i += 3) {
		glm::vec3 u = subMesh->vertis[i + 1] - subMesh->vertis[i];
		glm::vec3 v = subMesh->vertis[i + 2] - subMesh->vertis[i];

		glm::vec3 normal = glm::cross(u, v);
		subMesh->normals.push_back(normal);
		subMesh->normals.push_back(normal);
		subMesh->normals.push_back(normal);
	}
}

void Object::SetGlobal(SubMesh* subMesh) {
	for (int i = 0; i < subMesh->vertis.size(); i++) {
		subMesh->global.push_back(subMesh->vertis[i]);
		subMesh->global.push_back(subMesh->normals[i]);
	}
}