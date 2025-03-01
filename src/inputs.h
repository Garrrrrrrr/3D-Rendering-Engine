#include <stdlib.h>
#include <stdio.h>
#include "spheres.h"
#ifndef INPUTS_H
#define INPUTS_H
Sphere* getSpheres(FILE *inputFile);
unsigned int* getColor(FILE *inputFile, int m);
#endif