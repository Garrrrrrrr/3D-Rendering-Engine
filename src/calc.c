#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "math.h"
#include "spheres.h"

float calculateLighting(Vec3 intersectionPoint, Vec3 normal, Vec3 lightPos, float brightness, Sphere *spheres, int n, int currentSphere) {
    // Calculate light direction and distance
    Vec3 lightDir = normalize(subtract(lightPos, intersectionPoint)); 
    float lightDistance = length(subtract(lightPos, intersectionPoint)); 
    float dotProduct = fmaxf(0.0, dot(lightDir, normal)); 
    
    float intensity = brightness * dotProduct / (lightDistance * lightDistance);
    intensity = fmin(1.0, intensity); // Max 1.0

    // Shadow check
    Vec3 shadowRayOrigin = add(intersectionPoint, scalarMultiply(0.001, normal)); // Offset 
    for (int i = 0; i < n; i++) {
        if (i == currentSphere) continue; // Skip self
        float t;
        if (doesIntersect(&spheres[i], shadowRayOrigin, lightDir, &t)) {
            // Check if the intersection is closer than the light source
            if (t > 0.001 && t < lightDistance) {
                intensity *= 0.1; // 0.1 Shadow factor
                break;
            }
        }
    }
    return intensity;
}




