#include <custom/grid.h>
#include <stdlib.h>



struct Grid* CreateGrid(float width,float height,float cellHeight,float cellWidth)//cellHeight and Widht are not normalized
{
    int size=(width*height)/(cellWidth*cellHeight);
    struct Cell* temp =(struct Cell*) malloc(sizeof(struct Cell)*size);//Allocation of Cells
    unsigned int *tempIndices = malloc(sizeof(int)*(4*6*size));
    struct Grid* tempGrid=malloc(sizeof(struct Grid));
    tempGrid->cells=temp;
    tempGrid->indices= tempIndices;
    tempGrid->numberOfCells = size;
    float normHeight = (cellHeight/height)*2,normWidth = (cellWidth/width)*2;
    int MAXxFaux= width/cellWidth;
    int MAXyFaux= height/cellHeight;
    int x=0,y=0;
    int k=0;
    while (k < size)
    {
        temp[k].vert1.pos.x = x*normWidth-1;
        temp[k].vert1.pos.y = y*normHeight-1;

        temp[k].vert2.pos.x = (x+1)*normWidth-1;
        temp[k].vert2.pos.y = y*normHeight-1;

        temp[k].vert3.pos.x = (x+1)*normWidth-1;
        temp[k].vert3.pos.y = (y+1)*normHeight-1;

        temp[k].vert4.pos.x = x*normWidth-1;
        temp[k].vert4.pos.y = (y+1)*normHeight-1;
        tempIndices[0+6*k] = 0+4*k;
        tempIndices[1+6*k] = 3+4*k;
        tempIndices[2+6*k] = 2+4*k;
        tempIndices[3+6*k] = 0+4*k;
        tempIndices[4+6*k] = 2+4*k;
        tempIndices[5+6*k] = 1+4*k;

        k++;
        x++;
        if(x == MAXxFaux)
        {
            x=0;
            y++;
        }
    }


    return tempGrid;
}