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
    glBindBuffer(GL_ARRAY_BUFFER,0);
    strcpy(logbuff,"\n the vertex Context has been created\n");
    consoleLog();
    logbuff[0]='\0';
}
static void initiliseVAO(struct vertexContext* context)
{
    strcpy(logbuff,"\n the vertex Array Object creation has started\n");
    consoleLog();
    glGenVertexArrays(1,&context->VAO);
    strcpy(logbuff,"\n the vertex Array Object creation has ended\n");
    consoleLog();
}
static void initiliseVBO(struct vertexContext* context,GLsizeiptr size,const void* data,GLenum usage)
{
    strcpy(logbuff,"\n the vertex Buffer Object creation has started\n");
    consoleLog();
    glGenBuffers(1,&context->VBO);
    glBindBuffer(GL_ARRAY_BUFFER,context->VBO);
    glBufferData(GL_ARRAY_BUFFER,size,data,usage);
    strcpy(logbuff,"\n the vertex Buffer Object creation has ended\n");
    consoleLog();

}
static void initiliseEBO(struct vertexContext* context,int size,void * data)
{
    glGenBuffers(1, &(context->EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
static void initiliseVertexAttribiute(void (*callback)(struct vertexContext*),struct vertexContext* context)
{
    callback(context);
}
void enableVertextContext(struct vertexContext* context)
{
    glBindVertexArray(context->VAO);
}
void deleteVertexContext(struct vertexContext* context)
{
    glDeleteBuffers(1,&context->VBO);
    glDeleteBuffers(1,&context->EBO);
    glDeleteVertexArrays(1,&context->VAO);
}