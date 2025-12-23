#include <custom/vertex.h>
struct textureCoordOfCell
{
    struct vec2
    {
        float x;
        float y;
    };
    struct vec2 texCoord[4];
};
struct __attribute__((packed))  position
    {
        float x;
        float y;
        float z;
    };
struct __attribute__((packed))  texture
    {
        float x;
        float y;
};
struct __attribute__((packed))  vertex
{
    struct position pos;
    struct texture tex;
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
    struct Cell * fristIndexPointer //this exits soley for gpu side buffer estimation this shall not be used to do  anything cpu sided
};

const struct Grid* CreateGrid(float width,float height,float cellHeight,float cellWidth);
void SetCell(const struct Grid* grid,const struct textureCoordOfCell texCoord,const unsigned int);
void gridUpdate(struct vertexContext* context,const struct Grid* grid,unsigned int cellNO);
void GridTerminate(const struct Grid* grid);