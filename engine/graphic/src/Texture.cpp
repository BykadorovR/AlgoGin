#include "Texture.h"
Texture::Texture(char* FileName)
{
	m_fileName = FileName;
	imageId = 0;
	mGlTextureObject = 0;
}

bool Texture::Load()
{
	ilGenImages(1, &imageId);
	// ������ ����������� ������� 
	ilBindImage(imageId);

	// ���� �������� �������
	if (ilLoadImage(m_fileName))
	{
		// ���� �������� ������ ������� 
		// ��������� ������� ����������� 
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		// ���������� ����� ��� �� ������� 
		int bitspp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);

		switch (bitspp)// � ����������� �� ����������� ���������� 
		{
			// ������� �������� ��������� ����� GL_RGB ��� GL_RGBA 
		case 24:
			mGlTextureObject = MakeGlTexture(GL_RGB, ilGetData(), width, height);
			break;
		case 32:
			mGlTextureObject = MakeGlTexture(GL_RGBA, ilGetData(), width, height);
			break;
		}

		// ������� ������ 
		ilBindImage(0);
		ilDeleteImages(1, &imageId);
		return true;
	}
	else return false;
}

void Texture::Bind()
{
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mGlTextureObject);
}

GLuint Texture::MakeGlTexture(int Format, ILubyte* pixels, int w, int h)
{
	// ������������� ����������� ������� 
	GLuint texObject;

	// ���������� ���������� ������ 
	glGenTextures(1, &texObject);

	// ������������� ����� �������� �������� 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// ������� �������� � ������ ��� ��������� �������� 
	glBindTexture(GL_TEXTURE_2D, texObject);

	// ������������� ����� ���������� � ���������� �������� 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// ������� RGB ��� RGBA �������� 
	switch (Format)
	{
	case GL_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		break;

	case GL_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		break;
	}

	// ���������� ������������� ����������� ������� 
	return texObject;
}