#version 330 

in vec3 Position; 
in vec2 TexCoord;

uniform float ratio;

out vec2 TexCoord0;  

void main()
{
    gl_Position = vec4(Position.x/ratio, Position.yz, 1.0);
    TexCoord0 = TexCoord;
}