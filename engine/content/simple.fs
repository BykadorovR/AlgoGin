#version 330 

in vec2 TexCoord0;

uniform sampler2D gSampler;

out vec4 FragColor;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0.xy);
}