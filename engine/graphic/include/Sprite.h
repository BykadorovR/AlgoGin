#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Texture.h"

class Sprite
{
private:
	Texture* texture;
	float width;
	float height;
	Vector2f drawSize;
	Vector2f pos;
	Vector2f texCoords[4];
public:
	//sprite from texture
	Sprite(float _width, float _height, float posX, float posY, Texture* _t);
	//sprite from atlas
	Sprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t);
	void Draw(GLuint shaderProgram);
};