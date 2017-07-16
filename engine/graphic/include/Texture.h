#pragma once
#include <GL/glew.h>
#include <iostream>
#include <il.h>

class Texture
{
public:
	int width;
	int height;
	Texture(std::string FileName);
	bool Load();
	void Bind();
private:
	std::string m_fileName;
	ILuint imageId;
	GLuint mGlTextureObject;
	GLuint MakeGlTexture(int Format, ILubyte* pixels, int w, int h);
};