#include "color.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>
Vec3 unpackRGB(unsigned int packedRGB) {
    float red = ((packedRGB >> 16) & 0xFF) / 255.0f;
    float green = ((packedRGB >> 8) & 0xFF) / 255.0f;
    float blue = (packedRGB & 0xFF) / 255.0f;
    Vec3 color = {red, green, blue};
    return color;
}

void writeColour(FILE *ppmFile, Vec3 color) {
    int red = (int)(color.x * 255);
    int green = (int)(color.y * 255);
    int blue = (int)(color.z * 255);
    fprintf(ppmFile, "%d %d %d ", red, green, blue);
}

int compareColor(const void *a, const void *b)
{
    int a1 = 0, b1 = 0;
    for (int i = 0; i < sizeof(int); i++)
    {
        a1 |= (*((unsigned char*)a + i) & 0x0F) << (i * 8);
        b1 |= (*((unsigned char*)b + i) & 0x0F) << (i * 8);
    }
    
    return (a1 < b1) ? -1 : (b1 < a1) ? 1 : (*((int*)a) < *((int*)b)) ? -1 : (*((int*)a) > *((int*)b)) ? 1 : 0;
}