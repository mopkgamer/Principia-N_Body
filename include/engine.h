#pragma once

#include <stdio.h>
#include "..\include\linkedlist.h"
#include "..\include\vector.h"
#include "..\include\body.h"
#include "..\include\calculations.h"

void Run(LinkedList* Bodies, double deltaT, double endT, FILE* Output);