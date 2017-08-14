#pragma once
#include <GL/glew.h>
#include <iostream>
#include <il.h>

class Texture
{
public:
	int width;
	int height;
	Texture(std::string FileName, GLuint textureUnit);
	bool Load();
	void Bind();
	GLuint getTextureUnit();
private:
	std::string m_fileName;
	ILuint imageId;
	GLuint mGlTextureObject;
	GLuint textureUnit;
	GLuint MakeGlTexture(int Format, ILubyte* pixels, int w, int h);
};