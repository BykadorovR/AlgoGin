#pragma once
#include <GL/glew.h>
#include "Primitives.h"
#include "LightSource.h"
#include "Shader.h"
#include <vector>

class Lighting
{
private:
	std::vector<OmniLight*> omniLightSources;
	std::vector<DirectLight*> directLightSources;
	//Shader* shader;
public:
	void InitLighting(Shader* s);
	void Reposition(Shader* s);
	void AddOmniLightSource(Vector3f col, Vector3f vec, bool shadow);
	void AddDirectLightSource(Vector3f col, Vector3f vec, bool shadow);
	OmniLight* GetOmniLightSource(int i);
	DirectLight* GetDirectLightSource(int i);
};