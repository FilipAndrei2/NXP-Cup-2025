
#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
==================================================================================================*/
#include <stdbool.h>
#include "consts.h"
#include "utils.h"
#include "speed.h"
#include "hardware_interaction.h"
#include "Icu.h"
#include "CDD_Uart.h"
#include "distance_senzor.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
==================================================================================================*/
/*==================================================================================================
 *                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
 *                                      GLOBAL CONSTANTS
==================================================================================================*/

/*=================================================================================================
 *                                      GLOBAL VARIABLES
==================================================================================================*/
Adc_ValueGroupType AdcResultBuffer;
/*===================================================	===============================================
 *                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
 * @brief        Main function of the example
 * @details      Initializes the used drivers, hbridge, display, Pixy and servo.  The code
 *                  tries to keep the car between the two black lines using a Pixy2 camera.
 */




int main(void)
{
    DetectedVectors PixyVectors;
    DetectedVectors PixyVectors2;

    Vector2 averageVector, averageVector2;
    Vector temp;
    int direction1 = 0, direction2 = 0;
    uint8 state = 0;
    uint8 speed=0;
    _Bool ledState = true;
    double measuredAngles1 = 0.0;
    double measuredAngles2 = 0.0;
//    extern float distance;
//    extern uint8 terminatedFlag;
	extern int option;
	extern _Bool PL;
	extern _Bool displayOn;
    Init();
    // pentru intrerupere BTN0
    Icu_EnableEdgeDetection(1);
    Icu_EnableNotification(1);
    // pentru intrerupere BTN1
    Icu_EnableEdgeDetection(2);
    Icu_EnableNotification(2);
    // pentru potentiometru
    Adc_SetupResultBuffer(0 , &AdcResultBuffer);

    // pentru senzor de distanta
    Icu_EnableEdgeDetection(3);
	Icu_EnableNotification(3);

    EscSetSpeed(0);
    volatile int Delay = 5000000;
	while(Delay)
	{
		Delay--;
	}
	Delay = 5000000;
	while(Delay)
	{
		Delay--;
	}


    for (;;) {
    	if (displayOn) {

        	ledState = !ledState;
    		Dio_WriteChannel(111, ledState); // RED
    		Dio_WriteChannel(112, 1); // GREEN
    		Dio_WriteChannel(96, 1);  // BLUE
    	} else {
    		ChangeLedColor(1,0,1);
    	}
    	Pixy2GetVectors(&PixyVectors, 1), Pixy2GetVectors(&PixyVectors2, 2);
    	// pentru pornirea senzorului de distanta
//    	if (terminatedFlag == 1)
//    	{
//    		Dio_WriteChannel(17, 1);
//    		Delay = 10000;
//			while (Delay--);
//	    	Dio_WriteChannel(17, 0);
//    	}
    	// de la potentiometru
        Adc_StartGroupConversion(0);
        while (Adc_GetGroupStatus(0) == ADC_BUSY) {
        	;
        }

//		DisplayVectors(&PixyVectors);

		ValidateVectors(&PixyVectors);
		ValidateVectors(&PixyVectors2);

		switch (PixyVectors.NumberOfVectors)
		{
			case 1:
			{
				// Idee: putem sa folosim old averageVector
//				Vector2 oldAvg = averageVector;
				averageVector = GetVector2(PixyVectors.Vectors);
//				averageVector = ComputeAvgDiff(&oldAvg, &newAvg);
				break;
			}

			case 2:
				{
					Vector2 v0 = GetVector2(PixyVectors.Vectors);
					Vector2 v1 = GetVector2(PixyVectors.Vectors + 1);


//					if (isIntersection(&v0, &v1))
//					{
//						averageVector = GetVector2(&PixyVectors.Vectors[0]);
//					}
//					else
//					{
//						averageVector = Average(&v0, &v1);
//					}
					averageVector = Average(&v0, &v1);

//					// TEMP START
//					temp.x0=PixyVectors.Vectors[0].x0 / 2.0 + PixyVectors.Vectors[1].x0 / 2.0;
//					temp.y0=PixyVectors.Vectors[0].y0 / 2.0 + PixyVectors.Vectors[1].y0 / 2.0;
//					temp.x1=PixyVectors.Vectors[0].x1 / 2.0 + PixyVectors.Vectors[1].x1 / 2.0;
//					temp.y1=PixyVectors.Vectors[0].y1 / 2.0 + PixyVectors.Vectors[1].y1 / 2.0;
//
//					// TEMP END

					break;
				}
		}

		// Camera de jos
		switch (PixyVectors2.NumberOfVectors)
				{
					case 1:
					{
						averageVector2 = GetVector2(PixyVectors2.Vectors);
						break;
					}

					case 2:
						{
							Vector2 v0 = GetVector2(PixyVectors2.Vectors);
							Vector2 v1 = GetVector2(PixyVectors2.Vectors + 1);

							averageVector2 = Average(&v0, &v1);

//							// TEMP START ??
//							temp.x0=PixyVectors2.Vectors[0].x0 / 2.0 + PixyVectors2.Vectors[1].x0 / 2.0;
//							temp.y0=PixyVectors2.Vectors[0].y0 / 2.0 + PixyVectors2.Vectors[1].y0 / 2.0;
//							temp.x1=PixyVectors2.Vectors[0].x1 / 2.0 + PixyVectors2.Vectors[1].x1 / 2.0;
//							temp.y1=PixyVectors2.Vectors[0].y1 / 2.0 + PixyVectors2.Vectors[1].y1 / 2.0;
//
//							// TEMP END
							break;
						}
				}
		Normalize(&averageVector);
		Normalize(&averageVector2);

		measuredAngles1 = acos(-averageVector.point.y);
		measuredAngles2 = acos(-averageVector2.point.y);

		direction1 = ComputeDirection(&averageVector.point, measuredAngles1);
		direction2 = ComputeDirection(&averageVector2.point, measuredAngles2);

		if (displayOn)
		{
			DisplayClear();
			DisplayVectors(&PixyVectors2);
			DisplayValue(0U, (int)(AdcResultBuffer / 2.5), 3U, 0U);
			DisplayValue(1U, direction1, 4U, 0U);
			DisplayValue(2U, direction2, 4U, 0U);
			DisplayValue(7U, PL, 1U, 4U);
	//		DisplayValue(2U, (int)distance, 4U, 0U);
			ShowSpeedDisplay(option);
			DisplayRefresh();
		}
//		DisplayVector(NormalizePixyVector(temp));
		speed = ComputeSpeed(direction1);

		Steer(direction2);
		EscSetSpeed(speed);

	}
}
#ifdef __cplusplus
}
#endif

/** @} */
