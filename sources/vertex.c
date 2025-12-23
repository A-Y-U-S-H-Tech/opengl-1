#include <custom/vertex.h>
#include <custom/loger.h>
#include <string.h>
#include <glad/glad.h>
#include <stdio.h>

void initiliseVertexContext(struct vertexContext* context,GLsizeiptr size,const void* data,GLenum usage,void (*callback)(struct vertexContext*),int indicesSize,void* dataIndice)
{
    fflush(stdout);  
    strcpy(logbuff,"\n the vertex Context creation has started\n");
    consoleLog();
    initiliseVAO(context);
    enableVertextContext(context);
    initiliseVBO(context,size,data,usage);
    initiliseVertexAttribiute(callback,context);
    initiliseEBO(context,indicesSize,dataIndice);
    strcpy(logbuff,"\n the vertex Context has been created\n");
    consoleLog();
}
static void initiliseVAO(struct vertexContext* context)
{
    int glError=0;
    strcpy(logbuff,"\n the vertex Array Object creation has started\n");
    consoleLog();
    glGenVertexArrays(1,&context->VAO);
    glError = glGetError();
    strcpy(logbuff,"\n the vertex Array Object creation has ended\n");
    consoleLog();
}
static void initiliseVBO(struct vertexContext* context,GLsizeiptr size,const void* data,GLenum usage)
{
    int glError=0;
    strcpy(logbuff,"\n the vertex Buffer Object creation has started\n");
    consoleLog();
    glGenBuffers(1,&context->VBO);
    glError = glGetError();
    glBindBuffer(GL_ARRAY_BUFFER,context->VBO);
    glError = glGetError();
    glBufferData(GL_ARRAY_BUFFER,size,data,usage);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\nthe vertex Buffer Object creattion has failed\n");
        consoleLog();
        logFileAppend();
    }

}
static void initiliseEBO(struct vertexContext* context,int size,void * data)
{
    int glError=0;
    glGenBuffers(1, &(context->EBO));
    glError = glGetError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->EBO);
    glError = glGetError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\nthe initalization of the ebo has falied\n");
        consoleLog();
        logFileAppend();
    }

}
static void initiliseVertexAttribiute(void (*callback)(struct vertexContext*),struct vertexContext* context)
{
    int glError=0;
    callback(context);
    glError = glGetError();
}
void subVBOUpdate(struct vertexContext* context,int offset,int sizeOfData,const void* data)
{
    int glError=0;
    enableVertextContext(context);
    glBufferSubData(GL_ARRAY_BUFFER,offset,sizeOfData,data);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\n the upldation of data to sub buffer failed \n");
        consoleLog();
        logFileAppend();
    }

}
void enableVertextContext(struct vertexContext* context)
{
    int glError =0;
    glBindVertexArray(context->VAO);
    glError = glGetError();
    if(glError !=0)
    {
        strcpy(logbuff,"\n the vertex context couldn't be enabled \n");
        consoleLog();
        logFileAppend();
    }
}
void deleteVertexContext(struct vertexContext* context)
{
    int glError=0;
    glDeleteBuffers(1,&context->VBO);
    glDeleteBuffers(1,&context->EBO);
    glDeleteVertexArrays(1,&context->VAO);
    glError = glGetError();
    if(glError != 0)
    {
        strcpy(logbuff,"\n the deletion of vertex context has failed \n");
        consoleLog();
        logFileAppend();
    }
}