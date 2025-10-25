#include "utils.h"
#include <math.h>

void ValidateVectors(DetectedVectors* PixyVectors)
{
	if (!PixyVectors) return;

	for (int i = 0; i < PixyVectors->NumberOfVectors; ++i)
		{
			if (PixyVectors->Vectors[i].y0 > PixyVectors->Vectors[i].y1)
			{
				uint16 temp = PixyVectors->Vectors[i].y0;
				PixyVectors->Vectors[i].y0 = PixyVectors->Vectors[i].y1;
				PixyVectors->Vectors[i].y1 = temp;

				temp = PixyVectors->Vectors[i].x0;
				PixyVectors->Vectors[i].x0 = PixyVectors->Vectors[i].x1;
				PixyVectors->Vectors[i].x1 = temp;
			}
		}
}

Vector2 GetVector2(const Vector* v)
{
	Vector2 newV;

	newV.point.x = v->x0 - v->x1;
	newV.point.y = v->y0 - v->y1;
	newV.VectorIndex = v->VectorIndex;

	return newV;
}

double Length(const Vector2* v)
{
	return sqrt(v->point.x * v->point.x + v->point.y * v->point.y);
}

void Normalize(Vector2* v)
{
	double length = Length(v);

	if (fabs(length) < DBL_EPSILON)
	{
		v->point.x = 0;
		v->point.y = 0;
	} else {
		v->point.x /= length;
		v->point.y /= length;
	}
}

Vector2 Average(const Vector2* v1, const Vector2* v2)
{
	Vector2 result;

	result.point.x = v1->point.x / 2.0 + v2->point.x / 2.0;
	result.point.y = v1->point.y / 2.0 + v2->point.y / 2.0;
	result.VectorIndex = UNDEFINED_INDEX;

	return result;
}

int ComputeSpeed(int direction)
{
	int absoluteDir = (direction < 0) ? -direction : direction;
	if ( absoluteDir < 10) return 68;
	if ( absoluteDir > 40) return 55;
	return 50;
}

int ComputeDirection(const Point* pos, double angleRadians)
{
	// Just for test

	int sgn = signbit(pos->x) ? -1 : 1;

	return (int)lround(angleRadians * 63.66197723 * sgn); // 200 / PI
}


int isIntersection(Vector2* v1, Vector2* v2)
{
	double cosa = v1->point.x *v2->point.x + v1->point.y * v2->point.y;
	if (fabs(cosa) < 0.5)
	{
		return 1;
	}
	return 0;
}











