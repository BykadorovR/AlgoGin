#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"
#include <vector>

class SpritesHandler
{
private:
	std::vector <Sprite*> sprites;
	std::vector <Sprite*> spritesHUD;
	Shader* spritesShader;
	Shader* hudShader;
	float camWidth;
	float camHeight;
public:
	SpritesHandler(Shader* _spritesShader, Shader* _hudShader, float width, float height);
	void DrawSprites();
	void DrawHUD();

	void Create2DSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t);
	void Create2DSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t);

	void Create3DSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t);
	void Create3DSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t);

	void CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t);
	void CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t);

	Sprite* GetSprite(int i);
	Sprite* GetHUDSprite(int i);
};