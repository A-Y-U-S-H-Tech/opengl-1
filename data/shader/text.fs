#version 330 core

out vec4 FragColor;

in vec3 TexCoord;
uniform sampler2DArray ourTexture;
in vec4 Color;
void main()
{
    //FragColor = texture(ourTexture,TexCoord);
    // FragColor = vec4(0.0f,1.0f,1.0f, 1.0f);
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(ourTexture, TexCoord).r);
    FragColor = vec4(0.0f,1.0f,1.0f, 1.0) * sampled;
}