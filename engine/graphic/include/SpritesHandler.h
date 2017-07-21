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
	std::vector <Sprite*> sprites3D;
	std::vector <Sprite*> spritesHUD;
	Shader* spritesShader;
	Shader* hudShader;
	Vector2f cameraSize;
public:
	SpritesHandler(Shader* _spritesShader, Shader* _hudShader, Vector2f _cameraSize);
	void DrawSprites();
	void DrawHUD();

	void CreateSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t);
	void CreateSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t);

	void CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t);
	void CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t);

	Sprite* Get3DSprite(int i);
	Sprite* GetHUDSprite(int i);
};