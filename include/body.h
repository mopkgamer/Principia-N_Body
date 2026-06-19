#pragma once

#include "vector.h"

typedef struct Body3 Body3;

Body3* NewBody3(double Mass, double Radius, Vector3* Position, Vector3* InitialVelocity); // Creates a NEW Body3, which must be manually destroyed. NEVER free the Body's internal parameters. You can free the contructing parameters.

void SetBody3Mass(Body3* Body, double Mass);
void SetBody3Position(Body3* Body, Vector3* Position);
void SetBody3Velocity(Body3* Body, Vector3* Veclocity);

void ApplyForce(Body3* Body, Vector3* Force);
void EndForce(Body3* Body, Vector3* Force);
void ClearForces(Body3* Body);

Vector3* GetFres(Body3* Body);
Vector3* GetBody3Position(Body3* Body);
Vector3* GetBody3Velocity(Body3* Body);

double GetBody3Mass(Body3* Body);
double GetBody3Radius(Body3* Body);

void UpdateBody3Position(Body3* Body, double dt);
void UpdateBody3Velocity(Body3* Body, double dt);

void DestroyBody3(Body3* Body); // Clears all body internal parameters. NEVER free any of them yourself, unless you wish to manually destruct the Body3