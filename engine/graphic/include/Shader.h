#pragma once

#include "General.h"
#include <string>

class Shader {
private:
	std::string _vsPath;
	std::string _fsPath;
	GLuint _shaderProgram;

	void createShader();
	std::string readFile(std::string filePath);
	void addShader(std::string pShaderText, GLenum ShaderType);
public:
	Shader(std::string vsPath, std::string fsPath);
	void compileShaders();
	void useProgram();
	GLuint getProgram();
};