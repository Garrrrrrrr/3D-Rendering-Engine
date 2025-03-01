#include <stdlib.h>
#include <stdio.h>
#include "spheres.h"

unsigned int* getColor(FILE *inputFile, int m) {    
    unsigned int *color = malloc(m * sizeof(unsigned int)); // Cast unsigned int to the pointer returned by malloc (points to array of unsigned ints)
    for (int i = 0; i < m; i++) {
        if (fscanf(inputFile, "%x", &color[i]) != 1) {
            fprintf(stderr, "Error\n");
            exit(1);
        }
    }
    return color;
}

