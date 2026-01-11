#pragma once
#include <math.h>


struct Matrix3x3
{
    float Matrix[3][3];
};

struct Vector3D
{
    float vec[3];
    float size;
};
struct Vector2D
{
    int vec[3];
    int size;
};
struct Matrix4x4
{
    float Matrix[4][4];
};


void ScalerMatrix3x3Multiplication(struct Matrix3x3* A,float scaler);

struct Matrix3x3 CreateNullMatrix3x3(void);
struct Matrix3x3 CreateIdentityMatrix3X3(void);
struct Matrix3x3 AddMatrix3X3(struct Matrix3x3 A,struct Matrix3x3 B);
struct Matrix3x3 MultipleMatrix3X3(struct Matrix3x3 A,struct Matrix3x3 B);
float* GetMatrix3x3Pointer(struct Matrix3x3* A);

struct Matrix4x4 CreateNullMatrix4x4(void);
struct Matrix4x4 CreateIdentityMatrix4X4(void);
struct Matrix4x4 AddMatrix4X4(struct Matrix4x4 A,struct Matrix4x4 B);
struct Matrix4x4 MultipleMatrix4X4(struct Matrix4x4 A,struct Matrix4x4 B);
float* GetMatrix4x4Pointer(struct Matrix4x4* A);

struct Matrix4x4 Translate(struct Vector3D A);
struct Matrix4x4 RotateX(float angle);
struct Matrix4x4 Rotatey(float angle);
struct Matrix4x4 Rotatez(float angle);
struct Matrix3x3 ScreenProjection(float widht,float height);