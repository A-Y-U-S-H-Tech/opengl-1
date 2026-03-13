#pragma once
#include <glad/glad.h>
typedef struct vertexContext
{
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
} vertexContext;
void initiliseVertexContext(vertexContext* context,GLsizeiptr size,const void* data,GLenum usage,void (*callback)(vertexContext*),int indicesSize,void* dataIndice);
static void initiliseVertexAttribiute(void (*callback)(struct vertexContext*),vertexContext* context);
static void initiliseVAO(vertexContext* context);
static void initiliseVBO(vertexContext* context,GLsizeiptr size,const void* data,GLenum usage);
static void initiliseEBO(vertexContext* context,int size,void * data);
void subVBOUpdate(vertexContext* context,int offset,int sizeOfData,const void* data);
void enableVertextContext(vertexContext* context);
void deleteVertexContext(vertexContext* context);