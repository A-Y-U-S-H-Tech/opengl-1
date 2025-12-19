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
};

struct Grid* CreateGrid(float width,float height,float cellHeight,float cellWidth);