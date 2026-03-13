#pragma once
#include <custom/shader.h>
#include <custom/vertex.h>
#include <custom/ui/color.h>

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

struct Statictext{
    struct CharectorQuad* Quad;
    struct shaderContext* scontext;
    struct vertexContext*  vcontext;
    const unsigned int* textureID;//Pointer to a textureID of a charector collection
    const unsigned int* textureSampler;//Pointer to a TextureSampler of a charector collection
    unsigned int* indices;
};

struct GroupedStaticText{
    struct CharectorQuad* Quad;
    struct shaderContext* scontext;// can be shared between different type of texts
    struct vertexContext*  vcontext;// probhided to be shared between different types of texts
    const unsigned int maxSize;
    unsigned int sizeUsed;//it counts amount charector used and stored with the intention to be displayed
    unsigned int* indices;
    const unsigned int* textureID;//Pointer to a textureID of a charector collection
    const unsigned int* textureSampler;//Pointer to a TextureSampler of a charector collection
};



struct DynamicText
{
    struct CharectorQuad* Quad;
    struct shaderContext* scontext;// can be shared between different type of texts
    struct vertexContext*  vcontext;// probhided to be shared between different types of texts
    const unsigned int maxSize;//It is the maxSize allowed by the DynamicText
    unsigned int sizeUsed;//It counts the amount of charectors used in the dynmic text
    unsigned int* indices;
    const unsigned int* textureID;//Pointer to a textureID of a charector collection
    const unsigned int* textureSampler;//Pointer to a TextureSampler of a charector collection
};

//###############################################
//############|STATIC TEXT|######################
//###############################################

void initStaticText(const char* text,unsigned int textSize,const char* vertex);//to inilize StaticText struct with data to render a single line string 
void RenderStaticText();//uses data in a StaticText struct to Render the text on the screen

//################################################
//############|DYNAMIC TEXT|######################
//################################################

void initDynamicText();//to inilize the DynmicText struct with data to render max Possible charectoe decided by the user
void RenderDynamicText();//uses data in DynamicText struct to Render the visable(i.e used portion of screen) on the screen
void ModifyDynamicText();//to Modify the data in a DynamicText struct to Render a modified text

//#########################################################
//############|COLLECTION STATIC TEXT|######################
//##########################################################

void initCollectionStaticText();//to initilize the struct CollectionStaticText to handle multiple static Texts
void appendCollectionStaticText();//to add a static text to the CollectionStaticText struct
void RenderCollectionStaticText();//to display the visible text in the CollectionStaticText





void CreateStaticText(struct CharectorCollection* collection,float x,float y,const char* text,int textSize,struct color color);//loads frist 128 ASCII charector
struct Charector* loadCharectors(const char* filename,int size,unsigned int* texture,unsigned int sampler);//function to true true type fonts into a array of charector for better use
void RenderText(struct CharectorCollection *collection);
struct CharectorCollection* CreateCharectorCollection(int maxCharector,const char* vertexShader,const char* fragmentShader,unsigned int sampler,const char* filename,int size);//function to create charector collection
void DeleteCollection(struct CharectorCollection* collection);