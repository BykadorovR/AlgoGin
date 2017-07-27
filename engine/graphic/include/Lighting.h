#pragma once
#include <GL/glew.h>
#include "Primitives.h"
#include "LightSource.h"
#include "Shader.h"
#include <vector>

class Lighting
{
private:
	std::vector<LightSource*> lightSources;
	Shader* shader;
public:
	void InitLighting(Shader* s);
	void AddOmniLightSource(Vector3f col, Vector3f vec, bool shadow);
	void AddDirectLightSource(Vector3f col, Vector3f vec, bool shadow);
	LightSource* GetLightSource(int i);
};