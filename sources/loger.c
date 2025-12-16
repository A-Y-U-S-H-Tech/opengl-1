#include <custom/loger.h>
#include <stdio.h>
#include <string.h>
#include <glad/glad.h>
#include <stdlib.h>
char logbuff[525];
const char defaultfile[]="../data/file/log.txt";

void consoleLogLogerError(char * data)
{
    printf("[TIME] [Loging Error] [type]: %s",data);
}

void logFileAppend()
{
    FILE* ptr;
    ptr = fopen(defaultfile,"a+");
    if(ptr == NULL)
    {
        consoleLogLogerError("the file couldn't be opened\n");
        exit(1);
    }
    fputs(logbuff,ptr);
    fclose(ptr);
}
void consoleLog()
{
    printf("[TIME] [STATUS] : %s",logbuff);
}
void gllog()
{
    int temp;
    temp = glGetDebugMessageLog(2,500,NULL,NULL,NULL,NULL,NULL,logbuff);
    if(logbuff[0] != '\0')
    {
        strcat(logbuff,"\n");
        consoleLog();
        logFileAppend();
    }
}

void shaderChecker(unsigned int shader)
{
    int complied=0;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&complied);
    if(!complied)
    {
        glGetShaderInfoLog(shader,500,NULL,logbuff);
        strcat(logbuff,"\n");
        consoleLog();
        logFileAppend();
        logbuff[0]='\0';
    }
}

void programChecker(unsigned int program)
{
    int sucess=0;
    glGetProgramiv(program,GL_LINK_STATUS,&sucess);
    if(!sucess)
    {
        glGetProgramInfoLog(program,500,NULL,logbuff);
        strcat(logbuff,"\n");
        consoleLog();
        logFileAppend();
    }
}