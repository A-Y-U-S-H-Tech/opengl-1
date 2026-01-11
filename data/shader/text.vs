#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;
layout (location = 2) in vec4 aColor;

out vec3 TexCoord;
uniform mat3 transform;
out vec4 Color;

void main()
{
       gl_Position = vec4(transform*aPos,1.0);
       TexCoord = aTexCoord;
       Color = aColor;
}