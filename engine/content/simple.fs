#version 330 

in vec2 TexCoord0;

uniform sampler2D gSampler;
uniform float transparency = 1;

out vec4 FragColor;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0);
	FragColor.w *= transparency;
}