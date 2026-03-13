//all the function for shader 
#pragma once
typedef struct shaderContext
{
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int program;
}shaderContext;

char* fileload(const char *name);
void vShader( shaderContext* context,char* shaderfile);
void fShader(shaderContext* context,char* shaderfile);
struct shaderContext* CreateContext();
void enableShaderContext(shaderContext * context);
void DeleteShaderContext( shaderContext * context);
void useShaderContext(shaderContext* context);