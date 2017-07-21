#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Texture.h"
#include "Shader.h"
#include "MatrixHelper.h"

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
	Shader* spriteShader;
	bool isHUD;
public:
	//sprite from texture
	Sprite(float _width, float _height, float posX, float posY, Texture* _t, Shader* _s);
	Sprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t, Shader* _s);
	//sprite from atlas
	Sprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t, Shader* _s);
	Sprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t, Shader* _s);
	void Draw(GLuint sampler);
	void Translate(float x, float y, float z);
	void SetPos(float x, float y, float z);
	void Scale(float x, float y);
	void SetSize(float x, float y);
	void Rotate(float x, float y, float z);
	void SetRotation(float x, float y, float z);
};