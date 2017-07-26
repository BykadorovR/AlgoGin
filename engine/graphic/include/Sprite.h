#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>

class Sprite
{
private:
	Texture* texture;
	float width;
	float height;
	Vector3f pos;
	Vector3f rotate;
	Vector2f scale;
	Vector2f texCoord[2];
	Vertex Vertices[4];

	int rows;
	int cols;
	int currentFrame;
	std::vector<std::vector<int>> animations;
	std::vector<int> latency;
	int animationId;
	int frameId;
	int timer;
	GLuint VBO;
	GLuint IBO;
public:
	bool isHUD;
	bool isFollowingCamera;
	//sprite from texture
	Sprite(float _width, float _height, float posX, float posY, Texture* _t);
	Sprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t) : Sprite(_width, _height, posX, posY, _t)
	{
		pos.z = posZ;
		isHUD = false;
		CreateVertexBuffer();
	}
	//sprite from atlas
	Sprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t) : Sprite(_width, _height, posX, posY, _t)
	{
		texCoord[0] = Vector2f(coord0.x / _t->width, coord0.y / _t->height);
		texCoord[1] = Vector2f(coord1.x / _t->width, coord1.y / _t->height);
		Vertices[0].tex = texCoord[0];
		Vertices[1].tex = Vector2f(texCoord[0].x, texCoord[1].y);
		Vertices[2].tex = texCoord[1];
		Vertices[3].tex = Vector2f(texCoord[1].x, texCoord[0].y);
	}
	Sprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t) : Sprite(_width, _height, posX, posY, coord0, coord1, _t)
	{
		pos.z = posZ;
		isHUD = false;
		CreateVertexBuffer();
	}
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void Draw(GLuint program);
	GLuint GetTextureUnit();
	void Translate(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	Vector3f GetPosition();
	void Scale(float x, float y);
	void SetSize(float x, float y);
	void Rotate(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void FollowCamera(bool t);

	void MakeAnimated(int _cols, int _rows);
	void SetAnimationFrame(int i);
	void CreateAnimation(int n, int* frames, int l);
	void CreateAnimation(std::vector<int> frames, int l);
	void SetAnimation(int i);
	void NextAnimationFrame(int currenttime);
};