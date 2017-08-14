#version 330 

in vec3 Position; 
in vec2 TexCoord;
in vec3 Normal;     

uniform mat4 gWorld;
uniform mat4 lightBiasedMatrix;

out vec2 TexCoord0;  
out vec3 Normal0;     
out vec3 Position0; 
out vec4 ShadowCoord;

void main()
{
    gl_Position = gWorld * vec4(Position, 1.0);
	Position0 = Position;
    TexCoord0 = TexCoord;
	//Normal0 = (gWorld * vec4(Normal, 0.0)).xyz;
	Normal0 = Normal;
	ShadowCoord = lightBiasedMatrix * vec4(Position, 1.0);
}