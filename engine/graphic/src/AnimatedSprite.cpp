#include "AnimatedSprite.h"

/*#define CAMERA_WIDTH 1024
//#define CAMERA_HEIGHT 768

void AnimatedSprite::Draw(GLuint program)
{
	GLuint VBO, IBO;
	Vertex Vertices[4];

	Vector2f texCoordOffset = Vector2f(animframe[0] * (texCoords[2].x - texCoords[0].x), animframe[1] * (texCoords[2].y - texCoords[0].y));

	Vertices[0] = Vertex(Vector3f(-width / 2.0f, height / 2.0f, 0.0f), texCoords[0] + texCoordOffset);
	Vertices[1] = Vertex(Vector3f(-width / 2.0f, -height / 2.0f, 0.0f), texCoords[1] + texCoordOffset);
	Vertices[2] = Vertex(Vector3f(width / 2.0f, -height / 2.0f, 0.0f), texCoords[2] + texCoordOffset);
	Vertices[3] = Vertex(Vector3f(width / 2.0f, height / 2.0f, 0.0f), texCoords[3] + texCoordOffset);

	//Scale Vertices:
	for (int i = 0; i < 4; i++)
	{
		Vertices[i].pos.x *= scale.x;
		Vertices[i].pos.y *= scale.y;
	}
	//Rotate Vertices:
	Matrix4f m;
	m.InitRotateTransform(rotate.x, rotate.y, rotate.z);
	for (int i = 0; i < 4; i++)
	{
		Vertices[i].pos = m*Vertices[i].pos;
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

	GLuint a_position = glGetAttribLocation(program, "Position");
	GLuint a_texcoord = glGetAttribLocation(program, "TexCoord");

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void AnimatedSprite::SetAnimation(int _cols, int _rows)
{
	cols = _cols;
	rows = _rows;
	float texSizeX = texCoords[2].x - texCoords[0].x;
	float texSizeY = texCoords[2].y - texCoords[0].y;
	texCoords[1].y = texCoords[0].y + texSizeY / rows;
	texCoords[3].x = texCoords[0].x + texSizeX / cols;

	texCoords[2].x = texCoords[3].x;
	texCoords[2].y = texCoords[1].y;
}

void AnimatedSprite::SetAnimationFrame(int i, int j)
{
	animframe[0] = i % cols;
	animframe[1] = j % rows;
}*/