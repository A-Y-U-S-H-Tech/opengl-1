#pragma once
#include <custom/shader.h>
#include <custom/vertex.h>

struct CharectorVector
{
    float A;
    float B;
}; 

struct Charector
{
    unsigned int type;//what charector is it representing
    unsigned int Advance;
    unsigned int texture;
    struct CharectorVector size;
    struct CharectorVector bearing;
};

struct  __attribute__((packed)) charectorVertex{
    struct  __attribute__((packed)) position
    {
        float x;
        float y;
        float z;
    }m_pos;
    struct __attribute__((packed)) texCoords
    {
        float x;
        float y;
        float z;
    }m_texcoord;
    struct __attribute__((packed)) Color
    {
        float r;
        float g;
        float b;
        float alpha;
    }m_color;
};

struct  __attribute__((packed)) CharectorQuad
{
    struct charectorVertex v1;
    struct charectorVertex v2;
    struct charectorVertex v3;
    struct charectorVertex v4;
};

struct CharectorCollection
{
    struct CharectorQuad* Quad;
    struct Charector* charectors;
    struct shaderContext* scontext;
    struct vertexContext*  vcontext;
    unsigned int textureID;
    unsigned int textureSampler;
    unsigned int* indices;
    int size;
};

void CreateStaticText(struct CharectorCollection* collection,float x,float y,const char* text,int textSize);//loads frist 128 ASCII charector
struct Charector* loadCharectors(const char* filename,int size,unsigned int* texture,unsigned int sampler);//function to true true type fonts into a array of charector for better use
void RenderText(struct CharectorCollection *collection);
struct CharectorCollection* CreateCharectorCollection(int maxCharector,const char* vertexShader,const char* fragmentShader,unsigned int sampler,const char* filename,int size);//function to create charector collection
void DeleteCollection(struct CharectorCollection* collection);