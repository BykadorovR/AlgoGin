#include "Texture.h"
Texture::Texture(std::string FileName, GLuint _textureUnit)
{
	m_fileName = FileName;
	imageId = 0;
	mGlTextureObject = 0;
	textureUnit = _textureUnit;
	width = 0;
	height = 0;
}

bool Texture::Load()
{
	ilGenImages(1, &imageId);

	// set image to work with
	ilBindImage(imageId);

	// if load is successful
	if (ilLoadImage(m_fileName.c_str()))
	{
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		int bitspp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);

		switch (bitspp)
		{
		case 24:
			mGlTextureObject = MakeGlTexture(GL_RGB, ilGetData(), width, height);
			break;
		case 32:
			mGlTextureObject = MakeGlTexture(GL_RGBA, ilGetData(), width, height);
			break;
		}

		// memory clearing 
		ilBindImage(0);
		ilDeleteImages(1, &imageId);
		return true;
	}
	return false;
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glBindTexture(GL_TEXTURE_2D, mGlTextureObject);
}

GLuint Texture::MakeGlTexture(int Format, ILubyte* pixels, int w, int h)
{
	// texture unit id
	GLuint texObject;

	glGenTextures(1, &texObject);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, texObject);

	// filter and repeat modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// creating texture
	switch (Format)
	{
	case GL_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		break;

	case GL_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		break;
	}

	// return texture id
	return texObject;
}

GLuint Texture::getTextureUnit()
{
	return textureUnit;
}