#pragma once
#include <custom/vertex.h>
#include <custom/Sprite.h>
#include <custom/vector.h>
struct textureCoordOfCell
{
    vector2DF texCoord[4];
};
struct __attribute__((packed))  vertex
{
    struct vector3DF pos;
    struct vector2DF tex;
};

struct __attribute__((packed))  Cell
{
    struct vertex vert1;
    struct vertex vert2;
    struct vertex vert3;
    struct vertex vert4;
};

struct Grid
{ 
    struct Cell* cells;
    int numberOfCells;
    unsigned int* indices;
    struct Cell * fristIndexPointer ;//this exits soley for gpu side buffer estimation this shall not be used to do  anything cpu sided
};

const struct Grid* CreateGrid(float width,float height,float cellHeight,float cellWidth);
void SetCell(const struct Grid* grid,spriteCordinates texCoord,const unsigned int);
void gridUpdate(struct vertexContext* context,const struct Grid* grid,unsigned int cellNO);
void GridTerminate(const struct Grid* grid);