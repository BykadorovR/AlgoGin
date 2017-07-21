#include "SpritesHandler.h"

SpritesHandler::SpritesHandler(Shader* _spritesShader, Shader* _hudShader, Vector2f _cameraSize) : spritesShader(_spritesShader), hudShader(_hudShader), cameraSize(_cameraSize)
{
}
void SpritesHandler::DrawSprites()
{
	spritesShader->useProgram();
	GLuint gSampler = glGetUniformLocation(spritesShader->getProgram(), "gSampler");

	for each (Sprite* s in sprites3D)
	{
		s->Draw(gSampler);
	}
}
void SpritesHandler::DrawHUD()
{
	glDisable(GL_DEPTH_TEST);
	hudShader->useProgram();
	GLuint gSampler = glGetUniformLocation(hudShader->getProgram(), "gSampler");

	for each (Sprite* s in spritesHUD)
	{
		s->Draw(gSampler);
	}
	glEnable(GL_DEPTH_TEST);
}

void SpritesHandler::CreateSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t)
{
	sprites3D.push_back(new Sprite(_width, _height, posX, posY, posZ, _t, spritesShader));
}

void SpritesHandler::CreateSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	sprites3D.push_back(new Sprite(_width, _height, posX, posY, posZ, coord0, coord1, _t, spritesShader));
}

void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width, _height, posX, posY, _t, hudShader));
}

void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width, _height, posX, posY, coord0, coord1, _t, hudShader));
}

Sprite* SpritesHandler::Get3DSprite(int i)
{
	return sprites3D[i];
}

Sprite* SpritesHandler::GetHUDSprite(int i)
{
	return spritesHUD[i];
}