#include <stdio.h>

#include "include\linkedlist.h"
#include "include\vector.h"
#include "include\body.h"
#include "include\calculations.h"
#include "include\engine.h"

int main()  {
    Vector3* Position = NewVector3(0, 0, 0);
    Vector3* Position2 = NewVector3(10000, 0, 0);

    Vector3* Velocity2 = NewVector3(-100, 0, 0);

    Body3* B0 = NewBody3(1e20, 10, Position, Position);
    Body3* B1 = NewBody3(1e20, 10, Position2, Velocity2);

    LinkedList* Bodies = MakeLinkedList(B0, 40); // 40 is Hard-Coded, as the size of Body3
    AppendToLinkedList(Bodies, B1, 40);

    FILE* Output = fopen("Output.dat", "w");

    Run(Bodies, .001, 10, Output);
}