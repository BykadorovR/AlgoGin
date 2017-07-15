#pragma once
#include <GL/glew.h>
#include <il.h>

class Texture
{
public:
	Texture(char* FileName);
	bool Load();
	void Bind();
private:
	char* m_fileName;
	GLuint m_textureObj;
	ILuint imageId;
	GLuint mGlTextureObject;
	GLuint MakeGlTexture(int Format, ILubyte* pixels, int w, int h);
};