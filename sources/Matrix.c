#include <custom/Matrix.h>
#include <math.h>

struct Matrix3x3 CreateNullMatrix3x3(void)
{
    struct Matrix3x3 temp;
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        {
            temp.Matrix[i][j] =0;
        }
    }

    return temp;temp.Matrix[2][2] = 1;
}

struct Matrix3x3 CreateIdentityMatrix3X3(void)
{
    struct Matrix3x3 temp;
    temp = CreateNullMatrix3x3();
    temp.Matrix[0][0] = 1;
    temp.Matrix[1][1] = 1;
    temp.Matrix[2][2] = 1;

    return temp;
}
struct Matrix3x3 AddMatrix3X3(struct Matrix3x3 A,struct Matrix3x3 B)
{
    struct Matrix3x3 temp;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        {
            temp.Matrix[i][j] = A.Matrix[i][j] + A.Matrix[i][j];
        }
    }
    return temp;

}
struct Matrix3x3 MultipleMatrix3X3(struct Matrix3x3 A,struct Matrix3x3 B)
{
    struct Matrix3x3 R;
    R = CreateNullMatrix3x3();
    for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                for(int k =0;k<3;k++)
                {
                    R.Matrix[j][i]+=A.Matrix[j][k]*B.Matrix[k][i];
                }
            }
        }
    return R;
}
float* GetMatrix3x3Pointer(struct Matrix3x3* A)
{
    return (A->Matrix)[0];
}

void ScalerMatrix3x3Multiplication(struct Matrix3x3* A,float scaler)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            A->Matrix[i][j] *= scaler;
        }
    }
}

struct Matrix4x4 CreateNullMatrix4x4(void)
{
    struct Matrix4x4 temp;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
            temp.Matrix[i][j] =0;
        }
    }

    return temp;
}
struct Matrix4x4 CreateIdentityMatrix4X4(void)
{
    struct Matrix4x4 temp;
    temp = CreateNullMatrix4x4();
    temp.Matrix[0][0] = 1;
    temp.Matrix[1][1] = 1;
    temp.Matrix[2][2] = 1;
    temp.Matrix[3][3] = 1;

    return temp;
}
struct Matrix4x4 AddMatrix4X4(struct Matrix4x4 A,struct Matrix4x4 B)
{
    struct Matrix4x4 temp;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        {
            temp.Matrix[i][j] = A.Matrix[i][j] + A.Matrix[i][j];
        }
    }

    return temp;
}
struct Matrix4x4 MultipleMatrix4X4(struct Matrix4x4 A,struct Matrix4x4 B)
{
    struct Matrix4x4 R;
    R = CreateNullMatrix4x4();
    for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                for(int k =0;k<4;k++)
                {
                    R.Matrix[j][i]+=A.Matrix[j][k]*B.Matrix[k][i];
                }
            }
        }
    return R;
}
float* GetMatrix4x4Pointer(struct Matrix4x4* A)
{
    return (A->Matrix)[0];
}

struct Matrix4x4 Translate(struct Vector3D A)
{
    struct Matrix4x4 temp;
    temp = CreateIdentityMatrix4X4();
    temp.Matrix[0][3] = A.vec[0];
    temp.Matrix[1][3] = A.vec[1];
    temp.Matrix[2][3] = A.vec[2];
    return temp;
}


struct Matrix3x3 ScreenProjection(float widht,float height)
{
    struct Matrix3x3 temp = CreateIdentityMatrix3X3();
    temp.Matrix[0][0] = 2/widht;
    temp.Matrix[1][1] = 2/height;
    temp.Matrix[2][2] = 0;

    return temp;
}

struct Matrix4x4 RotateX(float angle)
{
    struct Matrix4x4 temp;
    temp = CreateNullMatrix4x4();
    temp.Matrix[0][0] = 1;
    temp.Matrix[1][1] = cos(angle);
    temp.Matrix[1][2] = -sin(angle);
    temp.Matrix[2][1] = sin(angle);
    temp.Matrix[2][2] = cos(angle);
    temp.Matrix[3][3] = 1;

    return temp;
}
struct Matrix4x4 Rotatey(float angle)
{
    struct Matrix4x4 temp;
    temp = CreateNullMatrix4x4();
    temp.Matrix[0][0] = cos(angle);
    temp.Matrix[0][2] = sin(angle);
    temp.Matrix[1][1] = 1;
    temp.Matrix[2][0] = -sin(angle);
    temp.Matrix[2][2] = cos(angle);
    temp.Matrix[3][3] = 1;

    return temp;
}
struct Matrix4x4 Rotatez(float angle)
{
    struct Matrix4x4 temp;
    temp = CreateNullMatrix4x4();
    temp.Matrix[0][0] = cos(angle);
    temp.Matrix[0][1] = -sin(angle);
    temp.Matrix[1][0] = sin(angle);
    temp.Matrix[1][1] = cos(angle);
    temp.Matrix[2][2] = 1;
    temp.Matrix[3][3] = 1;

    return temp;
}