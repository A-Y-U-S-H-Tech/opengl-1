#include <custom/vertex.h>
#include <custom/loger.h>
#include <string.h>
#include <glad/glad.h>

void initiliseVertexContext(struct vertexContext* context,GLsizeiptr size,const void* data,GLenum usage,void (*callback)(struct vertexContext*))
{
    strcpy(logbuff,"\n the vertex Context creation has started\n");
    consoleLog();
    initiliseVAO(context);
    initiliseVBO(context,size,data,usage);
    initiliseVertexAttribiute(callback,context);
    initiliseEBO(context);
    enableVertextContext(context);
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
    glBufferData(context->VBO,size,data,usage);
    glBindVertexArray(0);
    strcpy(logbuff,"\n the vertex Buffer Object creation has ended\n");
    consoleLog();

}
static void initiliseEBO(struct vertexContext* context)
{

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