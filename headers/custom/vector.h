#pragma once

typedef struct __attribute__((packed)) vector2DI
{
    int x;
    int y;
    int z;
} vector2DI;

typedef struct __attribute__((packed))  vector3DI
{
    int x;
    int y;
    int z;
} vector3DI;

typedef struct __attribute__((packed)) vector2DF{
    float  x;
    float  y;
}vector2DF;

typedef struct __attribute__((packed)) vector3DF
{
    float x;
    float y;
    float z;
}vector3DF;

typedef struct vectorND
{
    int* data;
    int size;
} vectorND;

vectorND* InitilizeVectorND(int size);