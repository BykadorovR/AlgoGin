#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Primitives.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"
#include "Camera.h"
#include <vector>

class SpritesHandler
{
private:
	std::vector <Sprite*> sprites;
	std::vector <Sprite*> spritesHUD;
	Shader* spritesShader;
	Shader* hudShader;
	Camera* camera;
public:
	SpritesHandler(Shader* _spritesShader, Shader* _hudShader, Camera* cam);
	void DrawSprites();
	void DrawHUD();

	void CreateSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t);
	void CreateSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t);

	void CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t);
	void CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t);

	Sprite* GetSprite(int i);
	Sprite* GetHUDSprite(int i);
};