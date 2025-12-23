//all the function for shader 

struct shaderContext
{
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int program;
};

char* fileload(const char *name);
void vShader(struct shaderContext* context,char* shaderfile);
void fShader(struct shaderContext* context,char* shaderfile);
struct shaderContext* CreateContext();
void enableShaderContext(struct shaderContext * context);
void DeleteShaderContext(struct shaderContext * context);
void useShaderContext(struct shaderContext* context);