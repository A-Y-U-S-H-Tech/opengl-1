#include <custom/grid.h>
#include <custom/vertex.h>
#include <stdlib.h>
#include <stdio.h>



const struct Grid* CreateGrid(float width,float height,float cellHeight,float cellWidth)//cellHeight and Widht are not normalized and are relative to widht and height of the grid
{
    int size=(width*height)/(cellWidth*cellHeight);
    struct Cell* temp =(struct Cell*) malloc(sizeof(struct Cell)*size);//Allocation of Cells
    unsigned int *tempIndices = malloc(sizeof(unsigned int)*(6*size));
    struct Grid* tempGrid=malloc(sizeof(struct Grid));
    tempGrid->cells=temp;
    tempGrid->indices= tempIndices;
    tempGrid->numberOfCells = size;
    tempGrid->fristIndexPointer = temp;
    float normHeight = (cellHeight/height)*2,normWidth = (cellWidth/width)*2;
    int MAXxFaux= width/cellWidth;
    int MAXyFaux= height/cellHeight;
    float xbias=1,ybias=1;
    int x=0,y=0;
    int k=0;
    while (k < size)
    {
        temp[k].vert1.pos.x = x*normWidth-xbias;
        temp[k].vert1.pos.y = y*normHeight-ybias;
        temp[k].vert1.pos.z = 0;
        temp[k].vert1.tex.x= 0;
        temp[k].vert1.tex.y= 0;

        temp[k].vert2.pos.x = (x+1)*normWidth-xbias;
        temp[k].vert2.pos.y = y*normHeight-ybias;
        temp[k].vert2.pos.z = 0;
        temp[k].vert2.tex.x= 0;
        temp[k].vert2.tex.y= 0;

        temp[k].vert3.pos.x = (x+1)*normWidth-xbias;
        temp[k].vert3.pos.y = (y+1)*normHeight-ybias;
        temp[k].vert3.pos.z = 0;
        temp[k].vert3.tex.x= 0;
        temp[k].vert3.tex.y= 0;

        temp[k].vert4.pos.x = x*normWidth-xbias;
        temp[k].vert4.pos.y = (y+1)*normHeight-ybias;
        temp[k].vert4.pos.z = 0;
        temp[k].vert4.tex.x= 0;
        temp[k].vert4.tex.y= 0;

        tempIndices[0+6*k] = 0+4*k;
        tempIndices[1+6*k] = 1+4*k;
        tempIndices[2+6*k] = 2+4*k;
        tempIndices[3+6*k] = 3+4*k;
        tempIndices[4+6*k] = 0+4*k;
        tempIndices[5+6*k] = 2+4*k;

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
void SetCell(const struct Grid* grid,const struct textureCoordOfCell texCoord,const unsigned int cellNO)
{
    grid->cells[cellNO].vert1.tex.x=texCoord.texCoord[0].x;
    grid->cells[cellNO].vert1.tex.y=texCoord.texCoord[0].y;
    
    grid->cells[cellNO].vert2.tex.x=texCoord.texCoord[1].x;
    grid->cells[cellNO].vert2.tex.y=texCoord.texCoord[1].y;

    grid->cells[cellNO].vert3.tex.x=texCoord.texCoord[2].x;
    grid->cells[cellNO].vert3.tex.y=texCoord.texCoord[2].y;

    grid->cells[cellNO].vert4.tex.x=texCoord.texCoord[3].x;
    grid->cells[cellNO].vert4.tex.y=texCoord.texCoord[3].y;
}
void gridUpdate(struct vertexContext* context,const struct Grid* grid,unsigned int cellNO)//Should be called only after inilization of the vertex Context
{
    int offset = sizeof(struct Cell)*(cellNO);
    int size = sizeof(struct Cell);
    void * data = (void*)(grid->fristIndexPointer);
    subVBOUpdate(context,offset,size,data+offset);
}
void GridTerminate(const struct Grid* grid)
{
    
    free(grid->indices);
    free(grid);
}