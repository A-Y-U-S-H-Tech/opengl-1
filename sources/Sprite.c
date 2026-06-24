#include <custom/Sprite.h>
#include <custom/shader.h>
#include <external/stdb_image.h>
#include <custom/loger.h>
#include <custom/DataStructure/Queue.h>
#include <glad/glad.h>
#include <custom/loger.h>
#include <stdio.h>
#include <string.h>

static void loadImage(ImageContext* img)
{
    stbi_set_flip_vertically_on_load(1);
    img->data = stbi_load(img->fileName,&(img->width),&(img->height),&(img->nrChannels),0);
    enQueue(&LogQueue,"\n the Image is loaded for the spirite\n");
}
SpriteSheetContext SetSpriteSheet(const char* filename,spriteParameter context)
{
    ImageContext img;
    img.fileName = filename;
    loadImage(&img);
    SpriteSheetContext spriteContext;
    spriteContext.sheetHeight = img.height;
    spriteContext.sheetWidth  = img.width;
    spriteContext.spriteHeight = context.height;
    spriteContext.spriteWidth   = context.width;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1,&spriteContext.TextureId);
    glBindTexture(GL_TEXTURE_2D,spriteContext.TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width,img.height,0,GL_RGBA,GL_UNSIGNED_BYTE,img.data);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    free(img.data);
    enQueue(&LogQueue,"\n the spriteContext is created\n");
    return spriteContext;
}
spriteCordinates GetSprite(SpriteSheetContext context,unsigned int spriteCellNO)
{
    int MaxX = context.sheetWidth/context.spriteWidth;
    int y = spriteCellNO/MaxX;
    int x = spriteCellNO -y*MaxX;
    
    spriteCordinates temp;

    temp.texCoord[0].x = ((float)x*context.spriteWidth)/context.sheetWidth;
    temp.texCoord[0].y = 1.0f - ((float)y*context.spriteHeight)/context.sheetHeight;

    temp.texCoord[1].x = ((float)(x+1)*context.spriteWidth)/context.sheetWidth;
    temp.texCoord[1].y = 1.0f - ((float)y*context.spriteHeight)/context.sheetHeight;

    temp.texCoord[2].x = ((float)(x+1)*context.spriteWidth)/context.sheetWidth;
    temp.texCoord[2].y = 1.0f - ((float)(y+1)*context.spriteHeight)/context.sheetHeight;

    temp.texCoord[3].x = ((float)x*context.spriteWidth)/context.sheetWidth;
    temp.texCoord[3].y = 1.0f - ((float)(y+1)*context.spriteHeight)/context.sheetHeight;

    return temp;
}
void useSpriteSheet(SpriteSheetContext context,struct shaderContext shaderContext,const char* TextureUniform)
{
    int location = glGetUniformLocation(shaderContext.program,TextureUniform);
    glUniform1i(location,0);
    int glError = glGetError();
    if(glError !=0)
    {
        enQueue(&LogQueue,"\n the vertex context couldn't be enabled \n");
    }
    enQueue(&LogQueue,"\nthe SpriteSheet is set in use\n");
}
void DeleteSpriteSheet(SpriteSheetContext context)
{
    glDeleteTextures(1,&context.TextureId);
    enQueue(&LogQueue,"\n the sprite sheet is deleted\n");
}