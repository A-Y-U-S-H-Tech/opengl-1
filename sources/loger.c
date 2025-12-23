#include <custom/loger.h>
#include <stdio.h>
#include <string.h>
#include <glad/glad.h>
#include <stdlib.h>
char logbuff[525];
const char defaultfile[]="data/file/log.txt";

void consoleLogLogerError(char * data)
{
    printf("[TIME] [Loging Error] [type]: %s",data);
}

void logFileAppend()
{
    fileptr = fopen(defaultfile,"a+");
    if(fileptr == NULL)
    {
        consoleLogLogerError("the file couldn't be opened\n");
        exit(2);
        
    }
    fputs(logbuff,fileptr);
    fflush(fileptr);
}
void consoleLog()
{
    printf("[TIME] [STATUS] : %s\n",logbuff);
}
void gllog()
{
    int temp;
    temp = glGetError();
    if(temp != 0)
    {
        snprintf(logbuff,500,"\nthere is an error in opengl code with error code : %d\n",temp);
        consoleLog();
        logbuff[0]='\0';
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