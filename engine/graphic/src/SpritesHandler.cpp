#include "SpritesHandler.h"
#include <math.h>

void SpritesHandler::Init(Shader* _spritesShader, Shader* _hudShader, Camera* cam)
{
	spritesShader = _spritesShader;
	hudShader = _hudShader;
	camera = cam;
	hudShader->useProgram();
	glUniform1f(glGetUniformLocation(hudShader->getProgram(), "ratio"), camera->getRatio());
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->CreateIndexBuffer();
		sprites[i]->CreateVertexBuffer();
	}
	for (int i = 0; i < spritesHUD.size(); i++)
	{
		spritesHUD[i]->CreateIndexBuffer();
		spritesHUD[i]->CreateVertexBuffer();
	}
}

void SpritesHandler::DrawSprites()
{
	spritesShader->useProgram();
	GLuint gSampler = glGetUniformLocation(spritesShader->getProgram(), "gSampler");
	GLuint transp = glGetUniformLocation(spritesShader->getProgram(), "transparency");
	for (int i = 0; i < sprites.size(); i++)
	{
		Sprite* s = sprites[i];
		glUniform1i(gSampler, s->GetTextureUnit());
		glUniform1f(transp, s->GetTransparency());
		if (s->isFollowingCamera)
		{
			/*float a = s->GetPosition().x - camera->getPosition().x;
			float b = s->GetPosition().z - camera->getPosition().z;
			float angle = asinf(b / sqrtf(a*a + b*b));
			if (a < 0) angle = -angle + M_PI;
			s->SetRotation(0, ToDegree(angle) + 90.0f, 0.0f);*/ //following by position

			s->SetRotation(-ToDegree(camera->getAngleV()) - 90.0f, ToDegree(camera->getAngleH()) + 90.0f, 0.0f); //following by both angles

			//s->SetRotation(0, ToDegree(camera->getAngleH()) + 90.0f, 0.0f); //following by one angle
		}
		s->Draw(spritesShader->getProgram());
	}
}

void SpritesHandler::DrawHUD()
{
	hudShader->useProgram();
	GLuint gSampler = glGetUniformLocation(hudShader->getProgram(), "gSampler");
	GLuint transp = glGetUniformLocation(spritesShader->getProgram(), "transparency");
	for (int i = 0; i < spritesHUD.size(); i++)
	{
		Sprite* s = spritesHUD[i];
		glUniform1i(gSampler, s->GetTextureUnit());
		glUniform1f(transp, s->GetTransparency());
		s->Draw(hudShader->getProgram());
	}
}
//===================CommonSprites===================
void SpritesHandler::CreateSprite(float _width, float _height, float posX, float posY, float posZ, Texture* _t)
{
	sprites.push_back(new Sprite(_width, _height, posX, posY, posZ, _t));
}
void SpritesHandler::CreateSprite(float _width, float _height, float posX, float posY, float posZ, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	sprites.push_back(new Sprite(_width, _height, posX, posY, posZ, coord0, coord1, _t));
}
//===================HUD===================
void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width, _height, posX, posY, _t));
}
void SpritesHandler::CreateHUDSprite(float _width, float _height, float posX, float posY, Vector2f coord0, Vector2f coord1, Texture* _t)
{
	spritesHUD.push_back(new Sprite(_width, _height, posX, posY, coord0, coord1, _t));
}

Sprite* SpritesHandler::GetSprite(int i)
{
	return sprites[i];
}

Sprite* SpritesHandler::GetHUDSprite(int i)
{
	return spritesHUD[i];
}