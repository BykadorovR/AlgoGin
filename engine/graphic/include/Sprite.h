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
	Vector2f texCoords[4];

	int rows;
	int cols;
	int currentFrame;
	std::vector<std::vector<int>> animations;
	int animationId;
	int frameId;
public:
	bool isHUD;
	bool isFollowingCamera;
	//sprite from texture
	Sprite(float _width, float _height, float posX, float posY, Texture* _t);
	Sprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t) : Sprite(_width, _height, posX, posY, _t)
	{
		pos.z = posZ;
		isHUD = false;
	}
	//sprite from atlas
	Sprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t) : Sprite(_width, _height, posX, posY, _t)
	{
		texCoords[0] = Vector2f(coord0.x / _t->width, coord0.y / _t->height);
		texCoords[1] = Vector2f(coord0.x / _t->width, coord1.y / _t->height);
		texCoords[2] = Vector2f(coord1.x / _t->width, coord1.y / _t->height);
		texCoords[3] = Vector2f(coord1.x / _t->width, coord0.y / _t->height);
	}
	Sprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t) : Sprite(_width, _height, posX, posY, coord0, coord1, _t)
	{
		pos.z = posZ;
		isHUD = false;
	}
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
	void CreateAnimation(int n, int* frames);
	void CreateAnimation(std::vector<int> frames);
	void SetAnimation(int i);
	void NextAnimationFrame();
};