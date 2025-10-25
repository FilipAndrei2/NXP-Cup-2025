#ifndef __UTILS__
#define __UTILS__

#include <math.h>
#include <float.h>
#include <stdlib.h>

//#include "PlatformTypes.h"

#include "consts.h"
#include "main_types.h"




void ValidateVectors(DetectedVectors*);
Vector2 Average(const Vector2* v1, const Vector2* v2);
Vector2 GetVector2(const Vector* v);
double Length(const Vector2* v);
void Normalize(Vector2* v);

int GetDirectionInt(double angleRadians);
int isIntersection(DetectedVectors *PixyVectors);
int ComputeDirection(const Point* pos,double angle);
//_Bool isStart(DetectedVectors* v);
_Bool validateTwoVectors(Vector* v1, Vector* v2);
//void DisplayVectorsPC(DetectedVectors* v);

#endif // __UTILS__
