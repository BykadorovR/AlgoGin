#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"

class AnimatedSprite : public Sprite
{
/*private:
	int rows;
	int cols;
	int animframe[2];
public:
	//sprite from texture
	AnimatedSprite(float _width, float _height, float posX, float posY, Texture* _t) : Sprite(_width, _height, posX, posY, _t)
	{
		rows = 1;
		cols = 1;
		animframe[0] = 0;
		animframe[1] = 0;
	}
	AnimatedSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t) : Sprite(_width, _height, posX, posY, posZ, _t)
	{
		rows = 1;
		cols = 1;
		animframe[0] = 0;
		animframe[1] = 0;
	}
	//sprite from atlas
	AnimatedSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t) : Sprite(_width, _height, posX, posY, coord0, coord1, _t)
	{
		rows = 1;
		cols = 1;
		animframe[0] = 0;
		animframe[1] = 0;
	}
	AnimatedSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t) : Sprite(_width, _height, posX, posY, posZ, coord0, coord1, _t)
	{
		rows = 1;
		cols = 1;
		animframe[0] = 0;
		animframe[1] = 0;
	}
	void Draw(GLuint program);
	void SetAnimation(int _cols, int _rows);
	void SetAnimationFrame(int i, int j);*/
};