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

typedef enum {
	DISPLAY_ON = 0,
    MIN_SPEED_OPTION,
    MED_SPEED_OPTION,
    MAX_SPEED_OPTION,
} Option_type_potentiometru;

void Init(void);
void DisplayVectors(DetectedVectors* PixyVectors);
int GetSteeringValueFromRadians(double angleRadians);
void One_milisecond_callback(void); // se apeleaza singura o data la 1ms
void ChangeLedColor(_Bool r, _Bool g, _Bool b);

#endif // __HARDWARE_INTERACTION__
