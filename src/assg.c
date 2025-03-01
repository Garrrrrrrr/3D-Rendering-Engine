#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "spheres.h"
#include "vector.h"
#include "color.h"
#include "calc.h"
#include "inputs.h"

int width, height, m, bgcolorI, n; // image width / height, num colours, bg colour index, num spheres
float vheight, flength, brightness; // viewport height, focal length, brightness
Vec3 lightPos, bgColor;
Viewport *viewport;
Sphere *spheres;
Vec3 cameraPos = {0.0, 0.0, 0.0};
int *color_index;
unsigned int *color, *pixels;

Sphere* getSpheres(FILE *inputFile) {
    if (fscanf(inputFile, "%d", &n) != 1){
        fprintf(stderr, "Error\n");
        exit(1);
    }
    Sphere *spheres = malloc(n * sizeof(Sphere)); // Reserve memory for n spheres
    color_index = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
    if (fscanf(inputFile, "%f %f %f %f %d", &spheres[i].pos.x, &spheres[i].pos.y, &spheres[i].pos.z, &spheres[i].r, &color_index[i]) != 5) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    spheres[i].color = unpackRGB(color[color_index[i]]);
    }
    return spheres;
}

void getInputs(FILE *inputFile) {
    viewport = malloc(sizeof(viewport));
    if (fscanf(inputFile, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    if (fscanf(inputFile, "%f", &viewport->height) != 1) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    if (fscanf(inputFile, "%f", &viewport->focalLength) != 1) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    if (fscanf(inputFile, "%f %f %f %f", &lightPos.x, &lightPos.y, &lightPos.z, &brightness) != 4){
        fprintf(stderr, "Error\n");
        exit(1);
    }
    if (fscanf(inputFile, "%d", &m) != 1){
        fprintf(stderr, "Error\n");
        exit(1);
    }
    color = getColor(inputFile, m); // Get color
    qsort(color, m, sizeof(unsigned int), compareColor); // qsort color
    if (fscanf(inputFile, "%d", &bgcolorI) != 1) {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    bgColor.x = 0; 
    bgColor.y=bgColor.z=bgColor.x;
    spheres = getSpheres(inputFile);
    viewport->width = viewport->height * ((float)width/height);
    pixels = malloc(width * height * sizeof(unsigned));
}
#ifdef MS1
void milestone1Output(FILE *outputFile, Vec3 bgColor, Vec3 lightPos, float vwidth, Sphere *spheres, int n) {
    Vec3 result;
	bgColor.x = bgColor.y = bgColor.z = 0; // hard code for ms1
    result = add(bgColor, lightPos);
    fprintf(outputFile, "(%.1f, %.1f, %.1f) + (%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",
            bgColor.x, bgColor.y, bgColor.z, lightPos.x, lightPos.y, lightPos.z, result.x, result.y, result.z);
    result = subtract(bgColor, lightPos);
    fprintf(outputFile, "(%.1f, %.1f, %.1f) - (%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",
            bgColor.x, bgColor.y, bgColor.z, lightPos.x, lightPos.y, lightPos.z, result.x, result.y, result.z);
    result = scalarMultiply(vwidth, lightPos);
    fprintf(outputFile, "%.1f * (%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",
            vwidth, lightPos.x, lightPos.y, lightPos.z, result.x, result.y, result.z);
    result = normalize(lightPos);
    fprintf(outputFile, "normalize(%.1f, %.1f, %.1f) = (%.1f, %.1f, %.1f)\n",
            lightPos.x, lightPos.y, lightPos.z, result.x, result.y, result.z);

    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "\n"); 
        spheres[i].color.x = spheres[i].color.z = spheres[i].color.y = 1; // hard code for ms1
        result = scalarDivide(spheres[i].color, spheres[i].r);
        fprintf(outputFile, "(%.1f, %.1f, %.1f) / %.1f = (%.1f, %.1f, %.1f)\n",
                spheres[i].color.x, spheres[i].color.y, spheres[i].color.z, spheres[i].r, result.x, result.y, result.z);
        float dotProduct = dot(lightPos, spheres[i].pos);
        fprintf(outputFile, "dot((%.1f, %.1f, %.1f), (%.1f, %.1f, %.1f)) = %.1f\n",
                lightPos.x, lightPos.y, lightPos.z, spheres[i].pos.x, spheres[i].pos.y, spheres[i].pos.z, dotProduct);
        float dist = distance(lightPos, spheres[i].pos);
        fprintf(outputFile, "distance((%.1f, %.1f, %.1f), (%.1f, %.1f, %.1f)) = %.1f\n",
                lightPos.x, lightPos.y, lightPos.z, spheres[i].pos.x, spheres[i].pos.y, spheres[i].pos.z, dist);
        float len = length(spheres[i].pos);
        fprintf(outputFile, "length(%.1f, %.1f, %.1f) = %.1f\n",
                spheres[i].pos.x, spheres[i].pos.y, spheres[i].pos.z, len);
    }
}

#elif MS2
Vec3 calcRayDir(int pX, int pY, Viewport *viewport, int height,  int width) {
    float x = (pX + 0.5) * (viewport->width / width) - (viewport->width / 2.0);
	float y = (viewport->height / 2.0) - (pY + 0.5) * (viewport->height / height);
	float z = -viewport->focalLength;
    Vec3 direction = {x, y, z};
    return normalize(direction);
}
void render(unsigned int *pixels, Sphere *spheres, unsigned int *colors, int *color_index){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Vec3 ray = calcRayDir(j, i, viewport, height, width);
            int hit = -1;
            float minT = -1;
            for (int k = 0; k < n; k++) {
                float t;
                if (doesIntersect(&spheres[k], cameraPos, ray, &t)) {
                    if (hit == -1 || t < minT) {
                        hit = k;
                        minT = t;
                    }
                }
            }
            if (hit == -1) {
                bgColor.x = bgColor.y = bgColor.z = 0;
                pixels[i * width + j] = ((int)(bgColor.x * 255) << 16) |
                                        ((int)(bgColor.y * 255) << 8) |
                                        (int)(bgColor.z * 255);
                continue;
            }
            Vec3 intersectionPoint = add(cameraPos, scalarMultiply(minT, ray));
            Vec3 normal = normalize(subtract(intersectionPoint, spheres[hit].pos));

            float intensity = calculateLighting(intersectionPoint, normal, lightPos, brightness, spheres, n, hit);
            int grayscaleValue = (int)(fminf(1.0, intensity) * 255);
            pixels[i * width + j] = (grayscaleValue << 16) | (grayscaleValue << 8) | grayscaleValue;
        }
    }
}

#elif FS
Vec3 calcRayDir(int pX, int pY, float offsetX, float offsetY, Viewport *viewport, int height, int width) {
    // Calculate the ray direction with offsets for anti-aliasing
    float x = (pX + offsetX) * (viewport->width / width) - (viewport->width / 2.0);
    float y = (viewport->height / 2.0) - (pY + offsetY) * (viewport->height / height);
    float z = -viewport->focalLength;
    Vec3 direction = {x, y, z};
    return normalize(direction);
}
void render(unsigned int *pixels, Sphere *spheres, unsigned int *colors, int *color_index) {
    int samplesPerPixel = 9; 
    float subPixelStep = 1.0f / 3.0f;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Vec3 finalColor = {0.0, 0.0, 0.0};
            // Loop 9 times per pixel
            for (int di = 0; di < 3; di++) {
                for (int dj = 0; dj < 3; dj++) {
                    // Calculate ray direction
                    float offsetX = (dj + 0.5f) * subPixelStep;
                    float offsetY = (di + 0.5f) * subPixelStep;
                    Vec3 ray = calcRayDir(j, i, offsetX, offsetY, viewport, height, width);

                    int hit = -1;
                    float minT = -1;
                    for (int k = 0; k < n; k++) {
                        float t;
                        if (doesIntersect(&spheres[k], cameraPos, ray, &t)) {
                            if (hit == -1 || t < minT) {
                                hit = k;
                                minT = t;
                            }
                        }
                    }
                    // No spehre hit
                    if (hit == -1) {
                        Vec3 bgColorVec = unpackRGB(color[bgcolorI]);
                        finalColor = add(finalColor, bgColorVec);
                        continue;
                    }
                    // Calculate intersection point and normal
                    Vec3 intersectionPoint = add(cameraPos, scalarMultiply(minT, ray));
                    Vec3 normal = normalize(subtract(intersectionPoint, spheres[hit].pos));
                    float intensity = fminf(1.0f, calculateLighting(intersectionPoint, normal, lightPos, brightness, spheres, n, hit));
                    // Compute subpixel color and add it to finalcolor
                    Vec3 subPixelColor = scalarMultiply(intensity, spheres[hit].color);
                    finalColor = add(finalColor, subPixelColor);
                }
            }
            // Average the finalColor
            finalColor = scalarDivide(finalColor, (float)samplesPerPixel);
            pixels[i * width + j] = ((int)(finalColor.x * 255) << 16) |
                                    ((int)(finalColor.y * 255) << 8) |
                                    (int)(finalColor.z * 255);
        }
    }
}

#endif


void writePPM(const char *filename, unsigned int *pixels, int width, int height) {
    FILE *outputFile = fopen(filename, "w");

    // Write PPM Header
    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", width, height);
    fprintf(outputFile, "255\n");

    // Write Pixel Data
    for (int i = 0; i < height * width; i++) {
        Vec3 color = unpackRGB(pixels[i]); // Convert packed color to Vec3
        writeColour(outputFile, color);   // Write color to file
        if ((i + 1) % width == 0) {
            fprintf(outputFile, "\n"); // New line at the end of each row
        }
    }

    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");    

    getInputs(inputFile);
    // MS1
    #ifdef MS1
    milestone1Output(outputFile, bgColor, lightPos, viewport->width, spheres, n);

    // MS2
    #elif MS2
    render(pixels, spheres, color, color_index);
    writePPM(argv[2], pixels, width, height);
    //FS
    #elif FS
    render(pixels, spheres, color, color_index);
    writePPM(argv[2], pixels, width, height);
    #endif

    
    // Close files, free memory
    fclose(inputFile);
    fclose(outputFile);    
    free(color);
    free(spheres);
    free(viewport);
    free(color_index);
    free(pixels);
    return 0;
}
