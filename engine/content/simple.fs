#version 330 

struct dirlight
{
	vec3 dir;
	vec3 col;
};

struct omnilight
{
	vec3 pos;
	vec3 col;
};

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 Position0; 

uniform sampler2D gSampler;
uniform float transparency = 1;
uniform omnilight omniLights[20];
uniform dirlight directLights[4];
uniform int omniLightsN;
uniform int directLightsN;

uniform vec3 eyePos;

out vec4 FragColor;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0);

	vec3 lightdir;
	float diffuseFactor;
	vec3 diffuseColor = vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < omniLightsN; i++)
	{
		lightdir = Position0 - omniLights[i].pos;
		diffuseFactor = max(0, dot(normalize(Normal0), normalize(lightdir)));
		float a =1/(1+length(lightdir));
		diffuseFactor *= 3*a;
		diffuseColor += diffuseFactor*vec3(omniLights[i].col);
	}
	for (int i = 0; i < directLightsN; i++)
	{
		lightdir = directLights[i].dir;
		diffuseFactor = max(0, dot(normalize(Normal0), lightdir));
		diffuseColor += diffuseFactor*vec3(directLights[i].col);
	}
	FragColor *= vec4(diffuseColor + vec3(0.1, 0.1, 0.2), 1.0);
	FragColor.w *= transparency;
}