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
    const char *temp = fileload(shaderfile);
    glShaderSource(context->vertexShader,1,&temp,NULL);
    glCompileShader(context->vertexShader);
    shaderChecker(context->vertexShader);
    free(temp);
}
void fShader(struct shaderContext* context,char* shaderfile)
{
    const char *temp = fileload(shaderfile);
    glShaderSource(context->fragmentShader,1,&temp,NULL);
    glCompileShader(context->fragmentShader);
    shaderChecker(context->fragmentShader);
    free(temp);
}
void enableShaderContext(struct shaderContext * context)
{
    glAttachShader(context->program,context->fragmentShader);
    glAttachShader(context->program,context->vertexShader);
    glLinkProgram(context->program);
    programChecker(context->program);
}
void useShaderContext(struct shaderContext* context)
{
    glUseProgram(context->program);
}
void DeleteShaderContext(struct shaderContext* context)
{
    glDeleteShader(context->fragmentShader);
    glDeleteShader(context->vertexShader);
    glDeleteProgram(context->program);
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