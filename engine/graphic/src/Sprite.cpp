#include "Sprite.h"

#define CAMERA_WIDTH 1024
#define CAMERA_HEIGHT 768

//sprite from texture
Sprite::Sprite(float _width, float _height, float posX, float posY, Texture* _t) : width(_width), height(_height), texture(_t)
{
	isHUD = true;
	isFollowingCamera = false;
	rotate = Vector3f(0.0f, 0.0f, 0.0f);
	scale = Vector2f(1.0f, 1.0f);
	pos = Vector3f(posX, posY, 0.0f);
	texCoord[0] = Vector2f(0, 0);
	texCoord[1] = Vector2f(1, 1);
	Vertices[0].tex = Vector2f(0, 0);
	Vertices[1].tex = Vector2f(0, 1);
	Vertices[2].tex = Vector2f(1, 1);
	Vertices[3].tex = Vector2f(1, 0);
	transparency = 1.0f;
	rows = 1;
	cols = 1;
	currentFrame = 0;
	animationId = 0;
	frameId = 0;
	timer = 0;
	CreateIndexBuffer();
	CreateVertexBuffer();
}

void Sprite::CreateIndexBuffer()
{
	glDeleteBuffers(1, &IBO);
	unsigned int Indices[] =
	{   0, 1, 2,
		2, 3, 0,
		4, 7, 6,
		6, 5, 4 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void Sprite::CreateVertexBuffer()
{
	glDeleteBuffers(1, &VBO);

	Vertices[0].pos = Vector3f(-width / 2.0f, height / 2.0f, 0.0f);
	Vertices[1].pos = Vector3f(-width / 2.0f, -height / 2.0f, 0.0f);
	Vertices[2].pos = Vector3f(width / 2.0f, -height / 2.0f, 0.0f);
	Vertices[3].pos = Vector3f(width / 2.0f, height / 2.0f, 0.0f);

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

	Vertices[4] = Vertices[0];
	Vertices[5] = Vertices[1];
	Vertices[6] = Vertices[2];
	Vertices[7] = Vertices[3];

	unsigned int Indices[] =
	{   0, 1, 2,
		2, 3, 0,
		4, 7, 6,
		6, 5, 4 };
	CalcNormals(Indices, 12, Vertices, 8);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void Sprite::Draw(GLuint program)
{
	CreateVertexBuffer();
	GLuint a_position = glGetAttribLocation(program, "Position");
	GLuint a_texcoord = glGetAttribLocation(program, "TexCoord");
	GLuint a_normal = glGetAttribLocation(program, "Normal");

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);
	glEnableVertexAttribArray(a_normal);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);
	glDisableVertexAttribArray(a_normal);
}

GLuint Sprite::GetTextureUnit()
{
	return texture->getTextureUnit();
}

void Sprite::Translate(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
	CreateVertexBuffer();
}

void Sprite::SetPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	CreateVertexBuffer();
}

Vector3f Sprite::GetPosition()
{
	return pos;
}

void Sprite::Scale(float x, float y)
{
	scale.x *= x;
	scale.y *= y;
	CreateVertexBuffer();
}

void Sprite::SetSize(float x, float y)
{
	scale.x = x;
	scale.y = y;
	CreateVertexBuffer();
}

void Sprite::Rotate(float x, float y, float z)
{
	rotate.x += x;
	rotate.y += y;
	rotate.z += z;
	CreateVertexBuffer();
}

void Sprite::SetRotation(float x, float y, float z)
{
	rotate.x = x;
	rotate.y = y;
	rotate.z = z;
	CreateVertexBuffer();
}

void Sprite::FollowCamera(bool t)
{
	isFollowingCamera = t;
}

void Sprite::SetTransparency(float _transparency)
{
	if (_transparency < 0)
	{
		transparency = 0.0f;
	}
	else
		if (_transparency > 1)
		{
			transparency = 1.0f;
		}
		else
			transparency = _transparency;
}

float Sprite::GetTransparency()
{
	return transparency;
}

void Sprite::MakeAnimated(int _cols, int _rows)
{
	cols = _cols;
	rows = _rows;
	float texSizeX = (texCoord[1].x - texCoord[0].x) / cols;
	float texSizeY = (texCoord[1].y - texCoord[0].y) / rows;
	texCoord[1].x = texCoord[0].x + texSizeX;
	texCoord[1].y = texCoord[0].y + texSizeY;
	Vertices[3].tex.x = texCoord[1].x;
	Vertices[1].tex.y = texCoord[1].y;

	Vertices[2].tex = texCoord[1];
}

void Sprite::SetAnimationFrame(int i)
{
	currentFrame = i%(rows*cols);

	Vector2f texCoordOffset = Vector2f((currentFrame%cols) * (texCoord[1].x - texCoord[0].x), (currentFrame / cols) * (texCoord[1].y - texCoord[0].y));
	Vertices[0].tex = texCoord[0] + texCoordOffset;
	Vertices[1].tex.x = texCoord[0].x + texCoordOffset.x;
	Vertices[1].tex.y = texCoord[1].y + texCoordOffset.y;
	Vertices[2].tex = texCoord[1] + texCoordOffset;
	Vertices[3].tex.x = texCoord[1].x + texCoordOffset.x;
	Vertices[3].tex.y = texCoord[0].y + texCoordOffset.y;
}

void Sprite::CreateAnimation(int n, int* frames, int l)
{
	std::vector<int> newAnim;
	for (int i = 0; i < n; i++)
	{
		newAnim.push_back(frames[i]);
	}
	animations.push_back(newAnim);
	latency.push_back(l);
	SetAnimation(animations.size() - 1);
}

void Sprite::CreateAnimation(std::vector<int> frames, int l)
{
	animations.push_back(frames);
	latency.push_back(l);
	SetAnimation(animations.size() - 1);
}

void Sprite::SetAnimation(int i)
{
	frameId = 0;
	animationId = i;
	SetAnimationFrame(animations[animationId][0]);
}

void Sprite::NextAnimationFrame(int currenttime)
{
	if (currenttime - timer > latency[animationId])
	{
		timer += latency[animationId]*((currenttime - timer)/latency[animationId]);
		frameId = (frameId + 1) % animations[animationId].size();
		SetAnimationFrame(animations[animationId][frameId]);
	}
}
