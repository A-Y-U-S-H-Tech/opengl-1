#include <glad/glad.h>
struct vertexContext
{
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
};
void initiliseVertexContext(struct vertexContext* context,GLsizeiptr size,const void* data,GLenum usage,void (*callback)(struct vertexContext*));
static void initiliseVertexAttribiute(void (*callback)(struct vertexContext*),struct vertexContext* context);
static void initiliseVAO(struct vertexContext* context);
static void initiliseVBO(struct vertexContext* context,GLsizeiptr size,const void* data,GLenum usage);
static void initiliseEBO(struct vertexContext* context);
void enableVertextContext(struct vertexContext* context);
void deleteVertexContext(struct vertexContext* context);