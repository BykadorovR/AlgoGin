#include "Lighting.h"

void Lighting::InitLighting(Shader* s)
{
	shader = s;
}

void Lighting::AddOmniLightSource(Vector3f col, Vector3f pos, bool shadow)
{
	lightSources.push_back(new OmniLight(col, pos));
	lightSources[lightSources.size() - 1]->SetShadows(shadow);
}

void Lighting::AddDirectLightSource(Vector3f col, Vector3f dir, bool shadow)
{
	lightSources.push_back(new DirectLight(col, dir));
	lightSources[lightSources.size() - 1]->SetShadows(shadow);
}

LightSource* Lighting::GetLightSource(int i)
{
	return lightSources[i];
}
