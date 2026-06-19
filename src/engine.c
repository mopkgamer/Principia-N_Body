#include <stdio.h>

#include "..\include\linkedlist.h"
#include "..\include\vector.h"
#include "..\include\body.h"
#include "..\include\calculations.h"

void Run(LinkedList* Bodies, double deltaT, double endT, FILE* Output)    {
    double T = 0;
    while (T < endT)
    {
        for (size_t i = 0; i < GetLinkedListLength(Bodies); i++)    {
            Body3* Body;
            Body = GetLinkedListDataAtIndex(Bodies, i);

            for (size_t j = 0; j < GetLinkedListLength(Bodies); j++)    {
                if (j == i) continue;
                Body3* Body2 = GetLinkedListDataAtIndex(Bodies, j);

                Vector3* F = AttractionForce(Body, Body2);
                ApplyForce(Body, F);

                DestroyVector3(F);
            }
        }
        // Pass 1: Set Body forces: Done

        for (size_t i = 0; i < GetLinkedListLength(Bodies); i++)    {
            Body3* Body;
            Body = GetLinkedListDataAtIndex(Bodies, i);

            UpdateBody3Velocity(Body, deltaT);
            UpdateBody3Position(Body, deltaT);
        }
        // Pass 2: Update Body velocities and positions: Done

        fprintf(Output, "\nt=%lfs\n\n", T);

        for (size_t i = 0; i < GetLinkedListLength(Bodies); i++)    {
            Body3* Body;
            Body = GetLinkedListDataAtIndex(Bodies, i);

            fprintf(Output, "Body%zu: Position=(%lf, %lf, %lf), Velocity=(%lf, %lf, %lf)\n", i,
            Vector3X(GetBody3Position(Body)), Vector3Y(GetBody3Position(Body)), Vector3Z(GetBody3Position(Body)),
            Vector3X(GetBody3Velocity(Body)), Vector3Y(GetBody3Velocity(Body)), Vector3Z(GetBody3Velocity(Body)));
        }
        // Pass 3: Print new info: Done

        for (size_t i = 0; i < GetLinkedListLength(Bodies); i++)    {
            Body3* Body;
            Body = GetLinkedListDataAtIndex(Bodies, i);

            ClearForces(Body);
        }
        // Pass 4: Clean up Forces: Done

        T += deltaT;

        fflush(Output);
    }

    for (size_t i = 0; i < GetLinkedListLength(Bodies); i++)    {
        Body3* Body;
        Body = GetLinkedListDataAtIndex(Bodies, i);

        DestroyBody3(Body);
        DestroyLinkedList(Bodies);
    }
}