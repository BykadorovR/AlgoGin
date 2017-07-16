#include "Sprite.h"

struct Vertex
{
	Vector3f m_pos;
	Vector2f m_tex;
	Vertex() {}
	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};
//sprite from texture
Sprite::Sprite(float _width, float _height, float posX, float posY, Texture* _t) : width(_width), height(_height), texture(_t)
{
	pos = Vector2f(posX, posY);
	texCoords[0] = Vector2f(0, 0);
	texCoords[1] = Vector2f(1, 0);
	texCoords[2] = Vector2f(1, 1);
	texCoords[3] = Vector2f(0, 1);
}
//sprite from atlas
Sprite::Sprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t) : width(_width), height(_height), texture(_t)
{
	pos = Vector2f(posX, posY);
	texCoords[0] = Vector2f(coord0.x / _t->width, coord0.y / _t->height);
	texCoords[1] = Vector2f(coord0.x / _t->width, coord1.y / _t->height);
	texCoords[2] = Vector2f(coord1.x / _t->width, coord1.y / _t->height);
	texCoords[3] = Vector2f(coord1.x / _t->width, coord0.y / _t->height);
}
void Sprite::Draw(GLuint shaderProgram)
{
	GLuint VBO, IBO;
	Vertex Vertices[4] = {
		Vertex(Vector3f((pos.x - width / 2) / 512 - 1, (pos.y - height / 2) / 384 - 1, 1.0f), texCoords[0]),
		Vertex(Vector3f((pos.x - width / 2) / 512 - 1, (pos.y + height / 2) / 384 - 1, 1.0f), texCoords[1]),
		Vertex(Vector3f((pos.x + width / 2) / 512 - 1, (pos.y + height / 2) / 384 - 1, 1.0f), texCoords[2]),
		Vertex(Vector3f((pos.x + width / 2) / 512 - 1, (pos.y - height / 2) / 384 - 1, 1.0f), texCoords[3]) };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	unsigned int Indices[] =
	{ 0, 1, 2,
		2, 3, 0 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	GLuint a_position = glGetAttribLocation(shaderProgram, "Position");
	GLuint a_texcoord = glGetAttribLocation(shaderProgram, "TexCoord");

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	texture->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);
}