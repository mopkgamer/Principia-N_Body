#pragma once

#include "vector.h"
#include "body.h"

Vector3* DistanceVector(Body3* B0, Body3* B1);
double Distance(Body3* B0, Body3* B1);

Vector3* AttractionForce(Body3* B0, Body3* B1);

void SetInEquatorialOrbit(Body3* CentralBody, Body3* OrbitingBody, double OrbitalRadius);