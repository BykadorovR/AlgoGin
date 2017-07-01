#pragma once

#include "General.h"
#include <string>

std::string readFile(std::string filePath);
void AddShader(GLuint ShaderProgram, std::string pShaderText, GLenum ShaderType);
void CompileShaders(std::string vsText, std::string fsText);