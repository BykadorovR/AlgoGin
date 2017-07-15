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
	// делаем изображение текущим 
	ilBindImage(imageId);

	// если загрузка удалась
	if (ilLoadImage(m_fileName))
	{
		// если загрузка прошла успешно 
		// сохраняем размеры изображения 
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		// определяем число бит на пиксель 
		int bitspp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);

		switch (bitspp)// в зависимости оп полученного результата 
		{
			// создаем текстуру используя режим GL_RGB или GL_RGBA 
		case 24:
			mGlTextureObject = MakeGlTexture(GL_RGB, ilGetData(), width, height);
			break;
		case 32:
			mGlTextureObject = MakeGlTexture(GL_RGBA, ilGetData(), width, height);
			break;
		}

		// очищаем память 
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
	// индетефекатор текстурного объекта 
	GLuint texObject;

	// генерируем текстурный объект 
	glGenTextures(1, &texObject);

	// устанавливаем режим упаковки пикселей 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// создаем привязку к только что созданной текстуре 
	glBindTexture(GL_TEXTURE_2D, texObject);

	// устанавливаем режим фильтрации и повторения текстуры 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// создаем RGB или RGBA текстуру 
	switch (Format)
	{
	case GL_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		break;

	case GL_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		break;
	}

	// возвращаем индетефекатор текстурного объекта 
	return texObject;
}