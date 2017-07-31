
in vec3 Position;

uniform mat4 lightWorld;

void main()
{
    gl_Position = lightWorld * vec4(Position, 1.0);
}