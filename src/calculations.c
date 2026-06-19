#include <math.h>
#include "..\include\calculations.h"

#define G 6.673e-11

Vector3* DistanceVector(Body3* B0, Body3* B1) {
    // r = pos1 - pos0  (from B0 to B1)
    Vector3* B0Pos = CloneVector3(GetBody3Position(B0));
    Vector3* B1Pos = CloneVector3(GetBody3Position(B1));

    MultiplyVector(B0Pos, -1.0);
    SumVector3(B1Pos, B0Pos);

    DestroyVector3(B0Pos);
    return B1Pos;
}

double Distance(Body3* B0, Body3* B1) {
    Vector3* d = DistanceVector(B0, B1);
    double Magnitude = Vector3Magnitude(d);
    DestroyVector3(d);
    return Magnitude;
}

Vector3* AttractionForce(Body3* B0, Body3* B1) {
    double M0 = GetBody3Mass(B0);
    double M1 = GetBody3Mass(B1);

    double r = Distance(B0, B1);
    if (r == 0.0) {
        return NewVector3(0.0, 0.0, 0.0);
    }

    double r2 = r * r;
    double lambda = (G * (M0 * M1)) / r2;

    Vector3* dir = DistanceVector(B0, B1);
    NormalizeVector3(dir);
    MultiplyVector(dir, lambda);

    return dir; // force vector
}

void SetInEquatorialOrbit(Body3* CentralBody, Body3* OrbitingBody, double OrbitalRadius) {
    Vector3* CPos = GetBody3Position(CentralBody);
    Vector3* tmp = NewVector3(Vector3X(CPos) + OrbitalRadius, Vector3Y(CPos), Vector3Z(CPos));
    SetBody3Position(OrbitingBody, tmp);
    DestroyVector3(tmp);

    Vector3* R = DistanceVector(CentralBody, OrbitingBody);
    NormalizeVector3(R);

    double Vx =  Vector3Y(R);
    double Vy = -Vector3X(R);
    DestroyVector3(R);

    Vector3* Tangent = NewVector3(Vx, Vy, 0.0);
    NormalizeVector3(Tangent);

    double Speed = sqrt(G * GetBody3Mass(CentralBody) / OrbitalRadius);
    MultiplyVector(Tangent, Speed);

    DestroyVector3(GetBody3Velocity(OrbitingBody));
    SumVector3(Tangent, GetBody3Velocity(CentralBody));
    SetBody3Velocity(OrbitingBody, Tangent);
    DestroyVector3(Tangent);
}
