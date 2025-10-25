#ifndef __UTILS__
#define __UTILS__

#include <math.h>
#include <float.h>
#include <stdlib.h>

//#include "PlatformTypes.h"

#include "consts.h"
#include "main_types.h"
#include "PID.h"



void ValidateVectors(DetectedVectors*);
Vector2 Average(const Vector2* v1, const Vector2* v2);
Vector2 GetVector2(const Vector* v);
double Length(const Vector2* v);
void Normalize(Vector2* v);

int GetDirectionInt(double angleRadians);
int isIntersection(Vector2* v1, Vector2* v2);
int ComputeSpeed(int direction);
int ComputeDirection(const Point* pos,double angle);

#endif // __UTILS__
