#include "Lighting.h"

void Lighting::InitLighting(Shader* s)
{
	Shader* shader = s;
	shader->useProgram();
	GLuint program = shader->getProgram();
	char str[20];
	for (int i = 0; i < omniLightSources.size(); i++)
	{
		sprintf(str, "omniLights[%d].col", i);
		glUniform3f(glGetUniformLocation(program, str), omniLightSources[i].GetColor().x, omniLightSources[i].GetColor().y, omniLightSources[i].GetColor().z);
		sprintf(str, "omniLights[%d].pos", i);
		glUniform3f(glGetUniformLocation(program, str), omniLightSources[i].GetPosition().x, omniLightSources[i].GetPosition().y, omniLightSources[i].GetPosition().z);
	}
	for (int i = 0; i < directLightSources.size(); i++)
	{
		sprintf(str, "directLights[%d].col", i);
		glUniform3f(glGetUniformLocation(program, str), directLightSources[i].GetColor().x, directLightSources[i].GetColor().y, directLightSources[i].GetColor().z);
		sprintf(str, "directLights[%d].dir", i);
		glUniform3f(glGetUniformLocation(program, str), directLightSources[i].GetDirection().x, directLightSources[i].GetDirection().y, directLightSources[i].GetDirection().z);
	}
	glUniform1i(glGetUniformLocation(program, "omniLightsN"), omniLightSources.size());
	glUniform1i(glGetUniformLocation(program, "directLightsN"), directLightSources.size());
}

void Lighting::AddOmniLightSource(Vector3f col, Vector3f pos, bool shadow)
{
	omniLightSources.push_back(OmniLight(col, pos));
	omniLightSources[omniLightSources.size() - 1].SetShadows(shadow);
}

void Lighting::AddDirectLightSource(Vector3f col, Vector3f dir, bool shadow)
{
	directLightSources.push_back(DirectLight(col, dir));
	directLightSources[directLightSources.size() - 1].SetShadows(shadow);
}

LightSource Lighting::GetOmniLightSource(int i)
{
	return omniLightSources[i];
}

LightSource Lighting::GetDirectLightSource(int i)
{
	return directLightSources[i];
}
