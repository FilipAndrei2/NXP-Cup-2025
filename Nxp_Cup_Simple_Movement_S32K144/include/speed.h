#ifndef __SPEED__H
#define __SPEED__H
#include "hardware_interaction.h"

void MinSpeed(void);
void MaxSpeed(void);
void MedSpeed(void);
uint8 ComputeSpeed(const int direction);
void ShowSpeedDisplay(Option_type_potentiometru option);
#endif // __SPEED__H
