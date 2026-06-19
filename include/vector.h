#pragma once

typedef struct Vector3 Vector3;

Vector3* NewVector3(double x, double y, double z); // Returns a NEW Vector3, which has to be manually destroyed; NULL on failure
Vector3* MakeNormalizedVector3(Vector3* Vector); // Returns a NEW Vector3, which has to be manually destroyed; NULL on failure
Vector3* MakeSumOfVector(Vector3* V0, Vector3* V1); // Returns a NEW Vector3, which has to be manually destroyed; NULL on failure
Vector3* MakeMultipliedVector(Vector3* Vector, double lambda); // Returns a NEW Vector3, which has to be manually destroyed; NULL on failure

double Vector3X(Vector3* Vector);
double Vector3Y(Vector3* Vector);
double Vector3Z(Vector3* Vector);
double Vector3Magnitude(Vector3* Vector);

void DestroyVector3(Vector3* Vector);
void NormalizeVector3(Vector3* Vector);
void SumVector3(Vector3* V0, Vector3* V1);
void MultiplyVector(Vector3* Vector, double lambda);

Vector3* CloneVector3(Vector3* Vector);