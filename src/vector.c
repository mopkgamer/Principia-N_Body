#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "..\include\vector.h"

struct Vector3  {
    double x;
    double y;
    double z;

    double magnitude;
};

Vector3* NewVector3(double x, double y, double z)   {
    Vector3* Vector = (Vector3*) malloc(sizeof(Vector3));

    if (!Vector) return NULL;

    Vector->x = x;
    Vector->y = y;
    Vector->z = z;

    Vector->magnitude = sqrt(x*x + y*y + z*z);

    return Vector;
}

Vector3* CloneVector3(Vector3* Vector)  {
    Vector3* NewVector = (Vector3*) malloc(sizeof(Vector3));

    if (!NewVector) return NULL;

    memcpy(NewVector, Vector, sizeof(Vector3));

    return NewVector;
}

Vector3* MakeNormalizedVector3(Vector3* Vector)  {
    Vector3* Clone = CloneVector3(Vector);
    
    if (!Clone) return NULL;
    
    double Magnitude = Clone->magnitude;

    NormalizeVector3(Clone);

    return Clone;
}

Vector3* MakeSumOfVector(Vector3* V0, Vector3* V1)   {
    Vector3* Clone = CloneVector3(V0);
    
    if (!Clone) return NULL;

    SumVector3(Clone, V1);

    return Clone;
}

Vector3* MakeMultipliedVector(Vector3* Vector, double lambda)    {
    Vector3* Clone = CloneVector3(Vector);
    
    if (!Clone) return NULL;

    MultiplyVector(Clone, lambda);

    return Clone;
}

double Vector3X(Vector3* Vector)    {
    return Vector->x;
}

double Vector3Y(Vector3* Vector)    {
    return Vector->y;
}

double Vector3Z(Vector3* Vector)    {
    return Vector->z;
}

double Vector3Magnitude(Vector3* Vector)    {
    return Vector->magnitude;
}

void DestroyVector3(Vector3* Vector)    {
    free(Vector);
}

void NormalizeVector3(Vector3* Vector)  {
    double lambda = 1/Vector->magnitude;

    MultiplyVector(Vector, lambda);
}

void SumVector3(Vector3* V0, Vector3* V1)   {
    V0->x += V1->x;
    V0->y += V1->y;
    V0->z += V1->z;

    V0->magnitude = sqrt(V0->x*V0->x + V0->y*V0->y + V0->z*V0->z);
}

void MultiplyVector(Vector3* Vector, double lambda) {
    Vector->x *= lambda;
    Vector->y *= lambda;
    Vector->z *= lambda;

    Vector->magnitude = sqrt(Vector->x*Vector->x + Vector->y*Vector->y + Vector->z*Vector->z);
}