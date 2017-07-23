#include "SpritesHandler.h"

SpritesHandler::SpritesHandler(Shader* _spritesShader, Shader* _hudShader, Camera* cam) : spritesShader(_spritesShader), hudShader(_hudShader), camera(cam)
{
}

void SpritesHandler::DrawSprites()
{
	spritesShader->useProgram();
	GLuint gSampler = glGetUniformLocation(spritesShader->getProgram(), "gSampler");
	for each (Sprite* s in sprites)
	{
		glUniform1i(gSampler, s->GetTextureUnit());
		if (s->isFollowingCamera)
		{
			//s->SetRotation(-ToDegree(camera->getAngleV()) - 90.0f, ToDegree(camera->getAngleH()) + 90.0f, 0.0f);//following by both coordinates
			s->SetRotation(0, ToDegree(camera->getAngleH()) + 90.0f, 0.0f);
		}
		s->Draw(spritesShader->getProgram(), camera->getWidth(), camera->getHeight());
	}
}

void SpritesHandler::DrawHUD()
{
	hudShader->useProgram();
	GLuint gSampler = glGetUniformLocation(hudShader->getProgram(), "gSampler");

	for each (Sprite* s in spritesHUD)
	{
		glUniform1i(gSampler, s->GetTextureUnit());
		s->Draw(hudShader->getProgram(), camera->getWidth(), camera->getHeight());
	}
}

//===================2D===================
void SpritesHandler::Create2DSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t)
{
	sprites.push_back(new Sprite(_width / (camera->getHeight() / 2), _height / (camera->getHeight() / 2), posX / (camera->getHeight() / 2) - 1, -posY / (camera->getHeight() / 2) + 1, posZ, _t));
}
void SpritesHandler::Create2DSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	sprites.push_back(new Sprite(_width / (camera->getHeight() / 2), _height / (camera->getHeight() / 2), posX / (camera->getHeight() / 2) - 1, -posY / (camera->getHeight() / 2) + 1, posZ, coord0, coord1, _t));
}
//===================3D===================
void SpritesHandler::Create3DSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t)
{
	sprites.push_back(new Sprite(_width, _height, posX, posY, posZ, _t));
}
void SpritesHandler::Create3DSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	sprites.push_back(new Sprite(_width, _height, posX, posY, posZ, coord0, coord1, _t));
}
//===================HUD===================
void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width / (camera->getWidth() / 2), _height / (camera->getHeight() / 2), posX / (camera->getWidth() / 2) - 1, -posY / (camera->getHeight() / 2) + 1, _t));
}
void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width / (camera->getWidth() / 2), _height / (camera->getHeight() / 2), posX / (camera->getWidth() / 2) - 1, -posY / (camera->getHeight() / 2) + 1, coord0, coord1, _t));
}

Sprite* SpritesHandler::GetSprite(int i)
{
	return sprites[i];
}

Sprite* SpritesHandler::GetHUDSprite(int i)
{
	return spritesHUD[i];
}