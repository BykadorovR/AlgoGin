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
in vec4 ShadowCoord;

uniform sampler2D gSampler;
uniform sampler2D shadowMap;
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

	vec3 lightdir, vertexToEye, lightReflect;
	float diffuseFactor, specularFactor;
	vec3 diffuseColor = vec3(0.0, 0.0, 0.0);
	vec3 specularColor = vec3(0.0, 0.0, 0.0);                                             

	for (int i = 0; i < directLightsN; i++)
	{
		lightdir = directLights[i].dir;
		diffuseFactor = max(0, dot(normalize(Normal0), normalize(lightdir)));
		diffuseColor += diffuseFactor*vec3(directLights[i].col);

		vertexToEye = normalize(eyePos - Position0);
		lightReflect = normalize(reflect(lightdir, Normal0));
		specularFactor = pow( max(0,dot(vertexToEye, lightReflect)), 16);
		specularColor += specularFactor*vec3(directLights[i].col);    
	}
	float visibility = 1.0;
	float bias = 0.005*tan(acos(dot(Normal0, lightdir))); // cosTheta is dot( n,l ), clamped between 0 and 1
	//bias = clamp(bias, 0,0.01);
	if (ShadowCoord.x < 1 && ShadowCoord.y < 1 && texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z - bias)
	{
		visibility = 0.0;
	}
	diffuseColor *= visibility;
	specularColor *= visibility;

	for (int i = 0; i < omniLightsN; i++)
	{
		lightdir = Position0 - omniLights[i].pos;

		diffuseFactor = max(0, dot(normalize(Normal0), normalize(lightdir)));
		float a =1/(1+length(lightdir));
		diffuseFactor *= 3*a;
		diffuseColor += diffuseFactor*vec3(omniLights[i].col);

		vertexToEye = normalize(eyePos - Position0);
		lightReflect = normalize(reflect(normalize(lightdir), Normal0));
		specularFactor = pow( max(0,dot(vertexToEye, lightReflect)), 16);
		specularColor += specularFactor*vec3(omniLights[i].col);    
	}

	FragColor *= vec4(diffuseColor + specularColor + vec3(0.1, 0.1, 0.2), 1.0);

	FragColor.w *= transparency;
}