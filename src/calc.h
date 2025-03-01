#include "vector.h"
#include "spheres.h"
#ifndef CALC_H
#define CALC_H
typedef struct {
    float width;
    float height;
    float focalLength;
} Viewport;

float calculateLighting(Vec3 intersectionPoint, Vec3 normal, Vec3 lightPos, float brightness, Sphere *spheres, int n, int currentSphere);

#endif