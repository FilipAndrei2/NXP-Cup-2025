#ifndef __HARDWARE_INTERACTION__
#define __HARDWARE_INTERACTION__

#include "display.h"

#include "display.h"
#include "receiver.h"
#include "CDD_I2c.h"
#include "esc.h"
#include "servo.h"
#include "linear_camera.h"
#include "main_functions.h"
#include "hbridge.h"
#include "Mcal.h"
#include "pixy2.h"

void Init(void);
void DisplayVectors(DetectedVectors* PixyVectors);
int GetSteeringValueFromRadians(double angleRadians);
void One_milisecond_callback(void); // se apeleaza singura o data la 1ms

#endif // __HARDWARE_INTERACTION__
