#pragma once

typedef struct vector2D
{
    int x;
    int y;
    int z;
} vector2D;
typedef struct vector3D
{
    int x;
    int y;
    int z;
} vector3D;
typedef struct vectorND
{
    int* data;
} vectorND;

vectorND* InitilizeVectorND(int size);