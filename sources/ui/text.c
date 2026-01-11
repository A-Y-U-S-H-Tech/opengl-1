#include <custom/ui/text.h>
#include <freetype2/ft2build.h>
#include <glad/glad.h>
#include FT_FREETYPE_H

#include <custom/shader.h>
#include <custom/vertex.h>

static int maxWidth=0;
static int maxHeight=0;
void max(FT_Face face)
{
    for (unsigned char i = 0; i < 128; i++)
    {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            printf("ERROR::FREETYTPE: Failed to load Glyph");  
        }//face->glyph->bitmap.width,face->glyph->bitmap.rows,0
        if(face->glyph->bitmap.rows > maxHeight){maxHeight = face->glyph->bitmap.rows;}
        if(face->glyph->bitmap.width > maxWidth){maxWidth = face->glyph->bitmap.width;}

    }
}

static void calllback(struct vertexContext* context)
{
    enableVertextContext(context);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(struct charectorVertex),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(struct charectorVertex),(void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(struct charectorVertex),(void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);
}


void CreateStaticText(struct CharectorCollection* collection,float x,float y,const char* text,int textSize)
{
    const int size = collection->size;
    float X=x;
    float Y=y;
    for(int i=0;i<textSize-1;i++)
    {
        collection->Quad[i+size].v1.m_pos.x = X;
        collection->Quad[i+size].v1.m_pos.y = Y;
        collection->Quad[i+size].v1.m_pos.z = 0;

        collection->Quad[i+size].v1.m_texcoord.x = 0;
        collection->Quad[i+size].v1.m_texcoord.y = collection->charectors[text[i]].size.B/maxHeight;
        collection->Quad[i+size].v1.m_texcoord.z = text[i];

        
        collection->Quad[i+size].v2.m_pos.x = X+collection->charectors[text[i]].size.A;
        collection->Quad[i+size].v2.m_pos.y = Y;
        collection->Quad[i+size].v2.m_pos.z = 0;

        collection->Quad[i+size].v2.m_texcoord.x = collection->charectors[text[i]].size.A/maxWidth;
        collection->Quad[i+size].v2.m_texcoord.y = collection->charectors[text[i]].size.B/maxHeight;
        collection->Quad[i+size].v2.m_texcoord.z = text[i];


        collection->Quad[i+size].v3.m_pos.x = X+collection->charectors[text[i]].size.A;
        collection->Quad[i+size].v3.m_pos.y = Y+collection->charectors[text[i]].size.B;
        collection->Quad[i+size].v3.m_pos.z = 0;

        collection->Quad[i+size].v3.m_texcoord.x = collection->charectors[text[i]].size.A/maxWidth;
        collection->Quad[i+size].v3.m_texcoord.y = 0;
        collection->Quad[i+size].v3.m_texcoord.z = text[i];

        collection->Quad[i+size].v4.m_pos.x = X;
        collection->Quad[i+size].v4.m_pos.y = Y+collection->charectors[text[i]].size.B;
        collection->Quad[i+size].v4.m_pos.z = 0;

        collection->Quad[i+size].v4.m_texcoord.x = 0;
        collection->Quad[i+size].v4.m_texcoord.y = 0;
        collection->Quad[i+size].v4.m_texcoord.z = text[i];

        collection->indices[0+6*i+size] = 0+4*i;//3
        collection->indices[1+6*i+size] = 1+4*i;//0
        collection->indices[2+6*i+size] = 2+4*i;//2
        collection->indices[3+6*i+size] = 3+4*i;//0
        collection->indices[4+6*i+size] = 0+4*i;
        collection->indices[5+6*i+size] = 2+4*i;
        X+=collection->charectors[text[i]].size.A;
    }
    collection->size+=textSize-1;
    subVBOUpdate(collection->vcontext,sizeof(struct CharectorQuad)*size,sizeof(struct CharectorQuad)*textSize,&collection->Quad[size]);
}
void init(struct CharectorCollection* collection,int max)
{
    for(int i=0;i<max;i++)
    {
        collection->Quad[i].v1.m_pos.x = 0;
        collection->Quad[i].v1.m_pos.y = 0;
        collection->Quad[i].v1.m_pos.z = 0;

        collection->Quad[i].v1.m_texcoord.x = 0;
        collection->Quad[i].v1.m_texcoord.y = 0;
        collection->Quad[i].v1.m_texcoord.z = 0;

        
        collection->Quad[i].v2.m_pos.x = 0;
        collection->Quad[i].v2.m_pos.y = 0;
        collection->Quad[i].v2.m_pos.z = 0;

        collection->Quad[i].v2.m_texcoord.x = 0;
        collection->Quad[i].v2.m_texcoord.y = 0;
        collection->Quad[i].v2.m_texcoord.z = 0;


        collection->Quad[i].v3.m_pos.x = 0;
        collection->Quad[i].v3.m_pos.y = 0;
        collection->Quad[i].v3.m_pos.z = 0;

        collection->Quad[i].v3.m_texcoord.x = 0;
        collection->Quad[i].v3.m_texcoord.y = 0;
        collection->Quad[i].v3.m_texcoord.z = 0;

        collection->Quad[i].v4.m_pos.x = 0;
        collection->Quad[i].v4.m_pos.y = 0;
        collection->Quad[i].v4.m_pos.z = 0;

        collection->Quad[i].v4.m_texcoord.x = 0;
        collection->Quad[i].v4.m_texcoord.y = 0;
        collection->Quad[i].v4.m_texcoord.z = 0;

        collection->indices[0+6*i] = 0+4*i;
        collection->indices[1+6*i] = 1+4*i;
        collection->indices[2+6*i] = 2+4*i;
        collection->indices[3+6*i] = 3+4*i;
        collection->indices[4+6*i] = 0+4*i;
        collection->indices[5+6*i] = 2+4*i;
    }
}
struct Charector* loadCharectors(const char* filename,int size,unsigned int* texture,unsigned int sampler)
{
    struct Charector* temp = malloc(sizeof(struct Charector)*128);

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        printf("ERROR::FREETYPE: Could not init FreeType Library\n");
    }

    FT_Face face;
    if (FT_New_Face(ft, filename, 0, &face))
    {
        printf("ERROR::FREETYPE: Failed to load font\n");
    }

    FT_Set_Pixel_Sizes(face, 0, size);
    max(face);
    glActiveTexture(GL_TEXTURE0+sampler);
    glGenTextures(1,texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glBindTexture(GL_TEXTURE_2D_ARRAY,*texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGetError();
    
    //glTexStorage3D(GL_TEXTURE_2D_ARRAY,0,GL_R8,size,size,128);
    //glTextureStorage3D(*texture, 0, GL_R8,face->glyph->bitmap.width*2, face->glyph->bitmap.rows*2, 128);
    glTexImage3D(GL_TEXTURE_2D_ARRAY,0,GL_R8,maxWidth,maxHeight,128,0,GL_RED,GL_UNSIGNED_BYTE,NULL);
    int error=0;
    for (unsigned char i = 0; i < 128; i++)
    {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            printf("ERROR::FREETYTPE: Failed to load Glyph");  
        }//face->glyph->bitmap.width,face->glyph->bitmap.rows,0
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY,0,0,0,i,face->glyph->bitmap.width,face->glyph->bitmap.rows,1,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
        
        error = glGetError();
        temp[i].Advance=face->glyph->advance.x;
        temp[i].size.A = (float) face->glyph->bitmap.width;
        temp[i].size.B = (float) face->glyph->bitmap.rows;
        temp[i].bearing.A = (float) face->glyph->bitmap_left;
        temp[i].bearing.B = (float) face->glyph->bitmap_top;
        temp[i].type = i;
        temp[i].texture=i;

    }
    free(face);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    return temp; 
}
void RenderText(struct CharectorCollection* collection)
{
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glActiveTexture(GL_TEXTURE0+collection->textureSampler);
    useShaderContext(collection->scontext);
    enableVertextContext(collection->vcontext);
}
struct CharectorCollection* CreateCharectorCollection(int maxCharector,const char* vertexShader,const char* fragmentShader,unsigned int sampler,const char* filename,int size)
{
    struct CharectorCollection* temp = malloc(sizeof(struct CharectorCollection));
    temp->charectors = loadCharectors(filename,size,&temp->textureID,sampler);
    temp->Quad = malloc(sizeof(struct CharectorQuad)*maxCharector);
    temp->indices = malloc(sizeof(unsigned int )*6*maxCharector);
    temp->textureSampler = sampler;
    temp->size = 0;
    temp->scontext = CreateContext();
    vShader(temp->scontext,vertexShader);
    fShader(temp->scontext,fragmentShader);
    enableShaderContext(temp->scontext);
    temp->vcontext = malloc(sizeof(struct vertexContext));
    init(temp,maxCharector);
    initiliseVertexContext(temp->vcontext,sizeof(struct CharectorQuad)*maxCharector,(void*)temp->Quad,GL_DYNAMIC_DRAW,calllback,sizeof(unsigned int)*6*maxCharector,(void*)temp->indices);
    return temp;
}
void DeleteCollection(struct CharectorCollection* collection)
{
    glActiveTexture(GL_TEXTURE0+collection->textureSampler);
    glBindTexture(GL_TEXTURE_2D_ARRAY,0);
    glDeleteTextures(1,&(collection->textureID));
    DeleteShaderContext(collection->scontext);
    deleteVertexContext(collection->vcontext);
    free(collection->Quad);
    free(collection->indices);
    free(collection);
}