#pragma once
#include <custom/shader.h>
struct spriteParameter
{
    float height;
    float width;
};
static struct ImageContext
{
    const char* data;
    int width,height, nrChannels;
    const char* fileName;
};
struct SpriteSheetContext
{
    unsigned int TextureId;
    int sheetHeight;
    int sheetWidth;
    int spriteHeight;
    int spriteWidth;
};
struct spriteCordinates
{
    struct vec2
    {
        float x;
        float y;
    };
    struct vec2 texCoord[4];
};
typedef  struct SpriteSheetContext  SpriteSheetContext;
typedef  struct spriteCordinates    spriteCordinates;
typedef  struct ImageContext ImageContext;
typedef  struct spriteParameter spriteParameter;

static void loadImage(ImageContext* img);
SpriteSheetContext SetSpriteSheet(const char* filename,spriteParameter context);
spriteCordinates GetSprite(SpriteSheetContext context,unsigned int spriteCellNO);
void useSpriteSheet(SpriteSheetContext context,struct shaderContext shaderContext,const char* TextureUniform); 
void DeleteSpriteSheet(SpriteSheetContext context);