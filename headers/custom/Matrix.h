#include <math.h>


struct Matrix3x4
{
    int Matrix[3][4];
    int Pointer[12];
};

struct Vector3D
{
    int vec[3];
    int size;
};
struct Vector2D
{
    int vec[3];
    int size;
};


void CrossMultiplication(struct vector3D);

void MatrixAddition(struct Matrix3x4* Result,struct Matrix3x4* A,struct Matrix3x4* B);
void MatrixMultiplication(struct Matrix3x4* Result,struct Matrix3x4* A,struct Matrix3x4* B);
void Rotation(struct Matrix3x4* Result,struct Matrix3x4* A,float Angle,struct Vector2D direction);//origin as Center