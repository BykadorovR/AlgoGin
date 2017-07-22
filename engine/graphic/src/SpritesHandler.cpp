#include "SpritesHandler.h"

SpritesHandler::SpritesHandler(Shader* _spritesShader, Shader* _hudShader, float width, float height) : spritesShader(_spritesShader), hudShader(_hudShader), camWidth(width), camHeight(height)
{

}

void SpritesHandler::DrawSprites()
{
	spritesShader->useProgram();
	GLuint gSampler = glGetUniformLocation(spritesShader->getProgram(), "gSampler");

	for each (Sprite* s in sprites)
	{
		s->Draw(gSampler, camWidth, camHeight);
	}
}

void SpritesHandler::DrawHUD()
{
	hudShader->useProgram();
	GLuint gSampler = glGetUniformLocation(hudShader->getProgram(), "gSampler");

	for each (Sprite* s in spritesHUD)
	{
		s->Draw(gSampler, camWidth, camHeight);
	}
}

//===================2D===================
void SpritesHandler::Create2DSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t)
{
	sprites.push_back(new Sprite(_width / (camHeight / 2), _height / (camHeight / 2), posX / (camHeight / 2) - 1, -posY / (camHeight / 2) + 1, posZ, _t, spritesShader));
}
void SpritesHandler::Create2DSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	sprites.push_back(new Sprite(_width / (camHeight / 2), _height / (camHeight / 2), posX / (camHeight / 2) - 1, -posY / (camHeight / 2) + 1, posZ, coord0, coord1, _t, spritesShader));
}
//===================3D===================
void SpritesHandler::Create3DSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t)
{
	sprites.push_back(new Sprite(_width, _height, posX, posY, posZ, _t, spritesShader));
}
void SpritesHandler::Create3DSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	sprites.push_back(new Sprite(_width, _height, posX, posY, posZ, coord0, coord1, _t, spritesShader));
}
//===================HUD===================
void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width / (camWidth / 2), _height / (camHeight / 2), posX / (camWidth / 2) - 1, -posY / (camHeight / 2) + 1, _t, hudShader));
}
void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width / (camWidth / 2), _height / (camHeight / 2), posX / (camWidth / 2) - 1, -posY / (camHeight / 2) + 1, coord0, coord1, _t, hudShader));
}

Sprite* SpritesHandler::GetSprite(int i)
{
	return sprites[i];
}

Sprite* SpritesHandler::GetHUDSprite(int i)
{
	return spritesHUD[i];
}