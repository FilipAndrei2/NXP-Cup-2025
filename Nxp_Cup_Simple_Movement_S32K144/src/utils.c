#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "hardware_interaction.h"
#include "params.h"
#include "CDD_Uart.h"
#include "Dio.h"
#define START_LINE_TOLERANCE (174)
#define DISTANCE_BETWEEN_TWO_LINES 30
#define VECT_DIM_CHAR 12

//Vector2* AverageVectorFromDetectedVectors(DetectedVectors* PixyVectors) {
//	Vector2* averageVector = NULL;
//	averageVector = (Vector2*) malloc(sizeof(Vector2));
//	if (!averageVector) {
//		ChangeLedColor(0, 1, 1);
//		return NULL;
//	}
//	switch (PixyVectors2.NumberOfVectors)
//	{
//		case 1:
//		{
//			averageVector2 = GetVector2(PixyVectors2.Vectors);
//			break;
//		}
//
//		case 2:
//			{
//				Vector2 v0 = GetVector2(PixyVectors2.Vectors);
//				Vector2 v1 = GetVector2(PixyVectors2.Vectors + 1);
//
//				averageVector2 = Average(&v0, &v1);
//
//				// TEMP START
//				temp.x0=PixyVectors2.Vectors[0].x0 / 2.0 + PixyVectors2.Vectors[1].x0 / 2.0;
//				temp.y0=PixyVectors2.Vectors[0].y0 / 2.0 + PixyVectors2.Vectors[1].y0 / 2.0;
//				temp.x1=PixyVectors2.Vectors[0].x1 / 2.0 + PixyVectors2.Vectors[1].x1 / 2.0;
//				temp.y1=PixyVectors2.Vectors[0].y1 / 2.0 + PixyVectors2.Vectors[1].y1 / 2.0;
//
//				// TEMP END
//				break;
//			}
//	}
//
//	return averageVector;
//}
//
//Vector2 ComputeAvgDiff(const Vector2* oldAvg, const Vector2* newAvg) {
//
//}
//
void ValidateVectors(DetectedVectors* PixyVectors)
{
	if (!PixyVectors || PixyVectors->NumberOfVectors == 0) return;

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

int ComputeDirection(const Point* pos, double angleRadians)
{
	// Just for test

	int sgn = signbit(pos->x) ? -1 : 1;

	return (int)lround(angleRadians * 63.66197723 * sgn); // 200 / PI
}


int isIntersection(DetectedVectors *PixyVectors)
{
//	double cosa = v1->point.x *v2->point.x + v1->point.y * v2->point.y;
//	if (fabs(cosa) < 0.5)
//	{
//		return 1;
//	}
//	return 0;

	if((PixyVectors->Vectors[0].y0 > 20)  || (PixyVectors->Vectors[0].y1 > 20))
	{
			return 0;
	}

	return 1;
}


Vector2 GetUnitVector(void)
{
	Vector2 newV;

	newV.point.x = 0;
	newV.point.y = -1;

	return newV;

}

//
//_Bool isStart(DetectedVectors* v) {
//	for (uint8 i = 0; i < v->NumberOfVectors/2; ++i) {
//		Vector2 v1 = GetVector2(v->Vectors + i);
//		double length1 = Length(&v1);
//		Normalize(&v1);
//
//		for (uint8 j = i+1; j < v->NumberOfVectors; ++j) {
//
//			Vector2 v2 = GetVector2(v->Vectors + j);
//			double length2 = Length(&v2);
//			Normalize(&v2);
//
//			_Bool areSameLength = labs((int)(length1*1000u) - (int)(length2*1000u)) < START_LINE_VECTORS_ACCEPTED_LENGHT_MINDIF;
//			_Bool areSameHeight = labs(
//									   (v->Vectors[0].y0 + v->Vectors[0].y1) / 2
//									 - (v->Vectors[1].y0 + v->Vectors[1].y1) / 2
//									  )
//								< START_LINE_VECTORS_ACCEPTED_HEIGHT_DELTA;
//
//			_Bool areHorizontal =  (labs((long)v1.point.x*1000) < START_LINE_VECTORS_ACCEPTED_ANGLE_HORIZ)
//								&& (labs((long)v2.point.x*1000) < START_LINE_VECTORS_ACCEPTED_ANGLE_HORIZ);
//
//			if (areSameLength && areSameHeight && areHorizontal) {
////				ChangeLedColor(1, 0, 1);
//				return true;
//			}
//		}
//		return false;
//	}
//
//	_Bool isStart2(DetectedVectors* v) {
//
//		for (uint8 i = 0; i < v->NumberOfVectors/2; ++i) {
//			Vector2 v1 = GetVector2(v->Vectors + i);
//			double length1 = Length(&v1);
//			Normalize(&v1);
//
//			for (uint8 j = i+1; j < v->NumberOfVectors; ++j) {
//
//				Vector2 v2 = GetVector2(v->Vectors + j);
//				double length2 = Length(&v2);
//				Normalize(&v2);
//
//
//				if () {
//	//				ChangeLedColor(1, 0, 1);
//					return true;
//				}
//			}
//			return false;
//
//	}
//
//	return false;
//}

_Bool validateTwoVectors(Vector* v1, Vector* v2) {
	Dio_WriteChannel(111, 0); // RED
	Dio_WriteChannel(112, 1); // GREEN
	Dio_WriteChannel(96, 1);  // BLUE
	int x0Diff, x1Diff;

	x0Diff = v1->x0 - v2->x0;
	x0Diff = x0Diff > 0 ? x0Diff : -x0Diff;
	x1Diff = v1->x1 - v2->x1;
	x1Diff = x1Diff > 0 ? x1Diff : -x1Diff;

	if (x0Diff > DISTANCE_BETWEEN_TWO_LINES && x1Diff > DISTANCE_BETWEEN_TWO_LINES) {
		return true;
	}
	return false;
}


//01 02 03 04 01 02 03 04\n
//void DisplayVectorsPC(DetectedVectors* v) {
//	if (v->NumberOfVectors == 0U) return;
//
//	char* buffer = (char*)malloc(VECT_DIM_CHAR);
//	if (buffer == NULL) return;
//
//
//	snprintf(buffer, VECT_DIM_CHAR, "%02d %02d %02d %02d ", v->Vectors->x0, v->Vectors->y0, v->Vectors->x1, v->Vectors->y1);
//
//	for (int i = 1; i < v->NumberOfVectors; ++i) {
//		char temp[VECT_DIM_CHAR];
//		sprintf(temp, "%02d %02d %02d %02d ", (v->Vectors + i)->x0, (v->Vectors + i)->y0, (v->Vectors + i)->x1, (v->Vectors + i)->y1);
//		buffer = (char*)strcat(buffer, temp);
//	}
//
//	buffer[VECT_DIM_CHAR * v->NumberOfVectors - 2] = '\n';
//	buffer[VECT_DIM_CHAR * v->NumberOfVectors - 1] = '\0';
//	Uart_SyncSend(0, buffer, VECT_DIM_CHAR * v->NumberOfVectors, 1000000);
//}



