#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


Vec3 add(Vec3 v1, Vec3 v2){
	Vec3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
Vec3 subtract(Vec3 v1, Vec3 v2){
	Vec3 result;
    	result.x = v1.x - v2.x;
    	result.y = v1.y - v2.y;
    	result.z = v1.z - v2.z;
    	return result;
}
Vec3 scalarMultiply(float s, Vec3 v) {
	Vec3 result;
	result.x = s * v.x;
	result.y = s * v.y;
	result.z = s * v.z;
	return result;
}
Vec3 scalarDivide(Vec3 v, float d){
	Vec3 result;
	if (d == 0) {
        result.x = result.y = result.z = 0;
    }
	result.x = v.x / d;
	result.y = v.y / d;
	result.z = v.z / d;
	return result;
}
Vec3 normalize(Vec3 v) {
	Vec3 result;
	float l = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.x = v.x / l;
	result.y = v.y / l;
	result.z = v.z / l;
	return result;
}
float dot(Vec3 v1, Vec3 v2){
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}
float length2(Vec3 v){
	float l = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return l;
}	
float length(Vec3 v){
	float l = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return l;
}
float distance2(Vec3 v1, Vec3 v2){
	float result;
	float x = v1.x - v2.x;
	float y = v1.y - v2.y;
	float z = v1.z - v2.z;
	return result = (x * x) + (y * y) + (z * z);
}
float distance(Vec3 v1, Vec3 v2){
	float result;
        float x = v1.x - v2.x;
        float y = v1.y - v2.y;
	float z = v1.z - v2.z;
        return result = sqrt((x * x) + (y * y) + (z * z));
}





