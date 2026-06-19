#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\include\body.h"
#include "..\include\linkedlist.h"

#define Vector3Size (4*sizeof(double))

struct Body3    {
    double Mass;
    double Radius;

    Vector3* Position;
    Vector3* Velocity;

    LinkedList* Forces;
};


Body3* NewBody3(double Mass, double Radius, Vector3* Position, Vector3* InitialVelocity)   {
    Body3* Body = (Body3*) malloc(sizeof(Body3));

    if (!Body) return NULL;

    LinkedList* Forces = MakeLinkedList(NULL, 0);

    if (!Forces) {
        free(Body);
        return NULL; 
    }

    Body->Mass = Mass;
    Body->Radius = Radius;
    Body->Position = CloneVector3(Position);
    Body->Velocity = CloneVector3(InitialVelocity);
    Body->Forces = Forces;

    return Body;
}

void SetBody3Mass(Body3* Body, double Mass) {
    Body->Mass = Mass;
}

void SetBody3Position(Body3* Body, Vector3* Position)   {
    Body->Position = CloneVector3(Position);
}

void SetBody3Velocity(Body3* Body, Vector3* Veclocity)  {
    Body->Velocity = CloneVector3(Veclocity);
}

void ApplyForce(Body3* Body, Vector3* Force)    {
    if (!Body->Forces) Body->Forces = MakeLinkedList(NULL, 0);
    if (!Body->Forces) return;
    AppendToLinkedList(Body->Forces, Force, Vector3Size);
}

void EndForce(Body3* Body, Vector3* Force)  {
    LinkedListNode* _Node = GetNodeFromData(Body->Forces, Force);
    if (_Node)  {
        size_t index = GetLinkedListNodeIndex(Body->Forces, _Node);
        RemoveFromLinkedList(Body->Forces, index);
    }
}
void ClearForces(Body3* Body)   {
    DestroyLinkedList(Body->Forces);
    Body->Forces = NULL;
}

Vector3* GetFres(Body3* Body)   {
    Vector3* Sum = NewVector3(0, 0, 0);

    if (Sum)    {
        for (size_t Index = 0; Index < GetLinkedListLength(Body->Forces); Index++)  {
            SumVector3(Sum, (Vector3*) GetLinkedListDataAtIndex(Body->Forces, Index));
        }
    }

    return Sum;
}

Vector3* GetBody3Position(Body3* Body)  {
    return Body->Position;
}

Vector3* GetBody3Velocity(Body3* Body)  {
    return Body->Velocity;
}

double GetBody3Mass(Body3* Body)    {
    return Body->Mass;
}

double GetBody3Radius(Body3* Body)  {
    return Body->Radius;
}

void UpdateBody3Position(Body3* Body, double dt)    {
    Vector3* TMP_VEL = MakeMultipliedVector(Body->Velocity, dt);

    SumVector3(Body->Position, TMP_VEL);

    DestroyVector3(TMP_VEL);
}

void UpdateBody3Velocity(Body3* Body, double dt)    {
    Vector3* Fres = GetFres(Body);

    double ax = Vector3X(Fres)/Body->Mass;
    double ay = Vector3Y(Fres)/Body->Mass;
    double az = Vector3Z(Fres)/Body->Mass;

    double dx = ax*dt;
    double dy = ay*dt;
    double dz = az*dt;

    DestroyVector3(Fres);

    Fres = NewVector3(dx, dy, dz);

    SumVector3(Body->Velocity, Fres);

    DestroyVector3(Fres);
}

void DestroyBody3(Body3* Body)  {
    DestroyVector3(Body->Position);
    DestroyVector3(Body->Velocity);
    DestroyLinkedList(Body->Forces);
    free(Body);
}