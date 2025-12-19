#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat2 transform;
out vec2 Pos;

void main()
{
       gl_Position = vec4(aPos.xy,0.0,1.0);
       TexCoord = aTexCoord;
       Pos = aPos.xy;
}