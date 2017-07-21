#include "Sprite.h"

#define CAMERA_WIDTH 1024.0f
#define CAMERA_HEIGHT 768.0f

struct Vertex
{
	Vector3f pos;
	Vector2f tex;
	Vertex() {}
	Vertex(Vector3f _pos, Vector2f _tex) : pos(_pos), tex(_tex)
	{
	}
};
//sprite from texture
Sprite::Sprite(float _width, float _height, float posX, float posY, Texture* _t, Shader* _s) : width(_width / (CAMERA_WIDTH / 2)), height(_height / (CAMERA_HEIGHT / 2)), texture(_t), spriteShader(_s)
{
	bool isHUD = true;
	rotate = Vector3f(0.0f, 0.0f, 0.0f);
	scale = Vector2f(1.0f, 1.0f);
	pos = Vector3f(posX / (CAMERA_WIDTH/2) - 1 , -posY / (CAMERA_HEIGHT/2) + 1, 0.0f);
	texCoords[0] = Vector2f(0, 0);
	texCoords[1] = Vector2f(1, 0);
	texCoords[2] = Vector2f(1, 1);
	texCoords[3] = Vector2f(0, 1);
}
Sprite::Sprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t, Shader* _s) : width(_width), height(_height), texture(_t), spriteShader(_s)
{
	bool isHUD = false;
	rotate = Vector3f(0.0f, 0.0f, 0.0f);
	scale = Vector2f(1.0f, 1.0f);
	pos = Vector3f(posX, posY, posZ);
	texCoords[0] = Vector2f(0, 0);
	texCoords[1] = Vector2f(1, 0);
	texCoords[2] = Vector2f(1, 1);
	texCoords[3] = Vector2f(0, 1);
}
//sprite from atlas
Sprite::Sprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t, Shader* _s) : width(_width/ (CAMERA_WIDTH / 2)), height(_height/ (CAMERA_HEIGHT / 2)), texture(_t), spriteShader(_s)
{
	bool isHUD = true;
	rotate = Vector3f(0.0f, 0.0f, 0.0f);
	scale = Vector2f(1.0f, 1.0f);
	pos = Vector3f(posX / (CAMERA_WIDTH / 2) - 1, -posY / (CAMERA_HEIGHT / 2) + 1, 0.0f);
	texCoords[0] = Vector2f(coord0.x / _t->width, coord0.y / _t->height);
	texCoords[1] = Vector2f(coord0.x / _t->width, coord1.y / _t->height);
	texCoords[2] = Vector2f(coord1.x / _t->width, coord1.y / _t->height);
	texCoords[3] = Vector2f(coord1.x / _t->width, coord0.y / _t->height);
}
Sprite::Sprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t, Shader* _s) : width(_width), height(_height), texture(_t), spriteShader(_s)
{
	bool isHUD = false;
	rotate = Vector3f(0.0f, 0.0f, 0.0f);
	scale = Vector2f(1.0f, 1.0f);
	pos = Vector3f(posX, posY, posZ);
	texCoords[0] = Vector2f(coord0.x / _t->width, coord0.y / _t->height);
	texCoords[1] = Vector2f(coord0.x / _t->width, coord1.y / _t->height);
	texCoords[2] = Vector2f(coord1.x / _t->width, coord1.y / _t->height);
	texCoords[3] = Vector2f(coord1.x / _t->width, coord0.y / _t->height);
}

void Sprite::Draw(GLuint sampler)
{
	glUniform1i(sampler, texture->getTextureUnit());

	GLuint VBO, IBO;
	Vertex Vertices[4];
	/*if (isHUD)
	{
		Vertices[0] = Vertex(Vector3f((pos.x - width / 2) / 512 - 1, (pos.y - height / 2) / 384 - 1, 1.0f), texCoords[0]);
		Vertices[1] = Vertex(Vector3f((pos.x - width / 2) / 512 - 1, (pos.y + height / 2) / 384 - 1, 1.0f), texCoords[1]);
		Vertices[2] = Vertex(Vector3f((pos.x + width / 2) / 512 - 1, (pos.y + height / 2) / 384 - 1, 1.0f), texCoords[2]);
		Vertices[3] = Vertex(Vector3f((pos.x + width / 2) / 512 - 1, (pos.y - height / 2) / 384 - 1, 1.0f), texCoords[3]);
	}
	else
	{*/
	Vertices[0] = Vertex(Vector3f(-width / 2.0f, -height / 2.0f, 0.0f), texCoords[0]);
	Vertices[1] = Vertex(Vector3f(width / 2.0f, -height / 2.0f, 0.0f), texCoords[1]);
	Vertices[2] = Vertex(Vector3f(width / 2.0f, height / 2.0f, 0.0f), texCoords[2]);
	Vertices[3] = Vertex(Vector3f(-width / 2.0f, height / 2.0f, 0.0f), texCoords[3]);
	//}

	//Scale Vertices:
	for (int i = 0; i < 4; i++)
	{
		Vertices[i].pos.x *= scale.x;
		Vertices[i].pos.y *= scale.y;
	}
	//Rotate Vertices:
	MatrixHelper m;

	if (isHUD)
	{
		m.setScale(Vector3f(1.0f, 1.0f, 1.0f));
		m.setPosition(Vector3f(0.0f, 0.0f, 0.0f));
		m.setRotate(Vector3f(rotate.x, rotate.y, 0.0f));
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].pos = m.getMatrix()*Vertices[i].pos;
		}
		m.setRotate(Vector3f(0.0f, 0.0f, rotate.z));
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].pos.x *= CAMERA_WIDTH;
			Vertices[i].pos.y *= CAMERA_HEIGHT;
			Vertices[i].pos = m.getMatrix()*Vertices[i].pos;
			Vertices[i].pos.x /= CAMERA_WIDTH;
			Vertices[i].pos.y /= CAMERA_HEIGHT;
		}
	}
	else
	{
		m.setScale(Vector3f(1.0f, 1.0f, 1.0f));
		m.setPosition(Vector3f(0.0f, 0.0f, 0.0f));
		m.setBackRotate(Vector3f(rotate.x, rotate.y, rotate.z));
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].pos = m.getMatrix()*Vertices[i].pos;
		}
	}

	//Translate Vertices:
	for (int i = 0; i < 4; i++)
	{
		Vertices[i].pos.x += pos.x;
		Vertices[i].pos.y += pos.y;
		Vertices[i].pos.z += pos.z;
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	unsigned int Indices[] =
	{ 0, 1, 2,
		2, 3, 0 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	GLuint a_position = glGetAttribLocation(spriteShader->getProgram(), "Position");
	GLuint a_texcoord = glGetAttribLocation(spriteShader->getProgram(), "TexCoord");

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);
}

void Sprite::Translate(float x, float y, float z)
{
	if (!isHUD)
	{
		pos.x += x;
		pos.y += y;
		pos.z += z;
	}
	else
	{
		pos.x += x/(CAMERA_WIDTH/2);
		pos.y -= y/(CAMERA_HEIGHT/2);
		pos.z += z;
	}
}

void Sprite::SetPos(float x, float y, float z)
{
	if (!isHUD)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}
	else
	{
		pos.x = x / (CAMERA_WIDTH / 2) - 1;
		pos.y = y / (CAMERA_HEIGHT / 2) + 1;
		pos.z = z;
	}
}

void Sprite::Scale(float x, float y)
{
	scale.x *= x;
	scale.y *= y;
}

void Sprite::SetSize(float x, float y)
{
	scale.x = x;
	scale.y = y;
}

void Sprite::Rotate(float x, float y, float z)
{
	rotate.x += x;
	rotate.y += y;
	rotate.z += z;
}

void Sprite::SetRotation(float x, float y, float z)
{
	rotate.x = x;
	rotate.y = y;
	rotate.z = z;
}