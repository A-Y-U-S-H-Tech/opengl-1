#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat3 transform;
uniform mat4 rotation;
out vec2 Pos;

void main()
{
       gl_Position = rotation*vec4(transform*aPos,1.0);
       TexCoord = aTexCoord;
       Pos = aPos.xy;
}