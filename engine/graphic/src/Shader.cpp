#include "Shader.h"
#include <iostream>
#include <fstream>
#include <cstring>

Shader::Shader(std::string vsPath, std::string fsPath) {
	_vsPath = vsPath;
	_fsPath = fsPath;
}

std::string Shader::readFile(std::string filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


void Shader::addShader(std::string pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar* p = pShaderText.c_str();
	GLint Lengths = pShaderText.length();
	glShaderSource(ShaderObj, 1, &p, &Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(_shaderProgram, ShaderObj);
}

void Shader::createShader() {
	_shaderProgram = glCreateProgram();

	if (_shaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
}

void Shader::compileShaders()
{
	createShader();
	// Read shaders
	std::string vertShaderStr = readFile(_vsPath);
	std::string fragShaderStr = readFile(_fsPath);

	addShader(vertShaderStr, GL_VERTEX_SHADER);
	addShader(fragShaderStr, GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(_shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(_shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}
}

void Shader::useProgram() {
	glUseProgram(_shaderProgram);
}

GLuint Shader::getProgram() {
	return _shaderProgram;
}