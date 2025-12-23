#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D ourTexture;
in vec2 Pos;
void main()
{
    FragColor = texture(ourTexture,TexCoord);
    //FragColor = vec4(abs(sin(Pos.x)), abs(cos(Pos.x)),abs(sin(Pos.x)), 1.0f);
}