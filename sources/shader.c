#include <custom/shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <string.h>
#include <custom/loger.h>

char* fileload(const char* name)
{
    FILE *ptr;
    ptr = fopen(name,"r");
    if(ptr == NULL)
    {
        strcpy(logbuff,"\n the file could not be opended file name: ");
        strcat(logbuff,name);
        strcat(logbuff,"\n");
        logFileAppend();
        consoleLog();
        logbuff[0]='\0';
        exit(1);
    }
    char *file = malloc(sizeof(char)*400);
    int bitsread = fread((void *)file,sizeof(char),400,ptr);
    file[bitsread]='\0';
    fclose(ptr);
    return file;
}
void vShader(struct shaderContext* context,char* shaderfile)
{
    int glError=0;
    const char *temp = fileload(shaderfile);
    glShaderSource(context->vertexShader,1,&temp,NULL);
    glError = glGetError();
    glCompileShader(context->vertexShader);
    glError = glGetError();
    if(glError != 0) 
    {
        strcpy(logbuff,"\n the vertex shader initilization has failed \n");
        consoleLog();
        logFileAppend();
    }
    shaderChecker(context->vertexShader);
    free(temp);
}
void fShader(struct shaderContext* context,char* shaderfile)
{
    int glError=0;
    const char *temp = fileload(shaderfile);
    glShaderSource(context->fragmentShader,1,&temp,NULL);
    glError = glGetError();
    glCompileShader(context->fragmentShader);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\n the fragment shader has failed to initalize \n");
        consoleLog();
        logFileAppend();
    }
    shaderChecker(context->fragmentShader);
    free(temp);
}
void enableShaderContext(struct shaderContext * context)
{
    int glError=0;
    glAttachShader(context->program,context->fragmentShader);
    glError = glGetError();
    glAttachShader(context->program,context->vertexShader);
    glError = glGetError();
    glLinkProgram(context->program);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\n the enabling of shader context has failed \n");
        consoleLog();
        logFileAppend();
    }
    programChecker(context->program);
}
void useShaderContext(struct shaderContext* context)
{
    int glError=0;
    glUseProgram(context->program);
    glError = glGetError();
    if(glError !=0)
    {
        strcpy(logbuff,"\n the apttempt to use the shader context falied \n");
        consoleLog();
        logFileAppend();
    }
}
void DeleteShaderContext(struct shaderContext* context)
{
    int glError=0;
    glDeleteShader(context->fragmentShader);
    glDeleteShader(context->vertexShader);
    glDeleteProgram(context->program);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\n the deletion of the shader failed \n");
        consoleLog();
        logFileAppend();
    }
    free(context);
}
struct shaderContext* CreateContext()
{
    struct shaderContext* temp = malloc(sizeof(struct shaderContext));
    temp->fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);;
    temp->vertexShader=  glCreateShader(GL_VERTEX_SHADER);
    temp->program= glCreateProgram();
    return temp;
}