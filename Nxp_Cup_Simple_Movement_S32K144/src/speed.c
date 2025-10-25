#include "speed.h"
#include <stdio.h>

extern Adc_ValueGroupType AdcResultBuffer;
extern _Bool PL;
extern _Bool displayOn;

uint8 minSpeed = 53; // 40
uint8 medSpeed = 60; // 50 60
uint8 maxSpeed = 75; // 70

void MinSpeed(void) {
	minSpeed = AdcResultBuffer / 2.5;
}

void MaxSpeed(void) {
	maxSpeed = AdcResultBuffer / 2.5;
}

void MedSpeed(void) {
	medSpeed = AdcResultBuffer / 2.5;
}

uint8 ComputeSpeed(const int direction)
{
	int absoluteDir = (direction < 0) ? -direction : direction;
	if (absoluteDir < 15) return maxSpeed;
	if (absoluteDir > 30) return minSpeed;
	return medSpeed;
}

void ShowSpeedDisplay(Option_type_potentiometru option){
	DisplayValue(4U, displayOn, 1U, 0U);
	DisplayValue(5U, minSpeed, 3U, 0U);
	DisplayValue(6U, medSpeed, 3U, 0U);
	DisplayValue(7U, maxSpeed, 3U, 0U);
	DisplayText(option + 4, "-", 1U, 3U);
}
