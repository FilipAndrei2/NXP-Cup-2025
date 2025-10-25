
#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
==================================================================================================*/
#include "consts.h"
#include "utils.h"
#include "hardware_interaction.h"
#include "CDD_Uart.h"
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

/*==================================================================================================
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
    Vector2 averageVector;
    Vector temp;
    int direction = 0;

    int speed = 0;
    volatile int Delay = 5000000;
    while(Delay)
    {
    	Delay--;
    }
    EscSetSpeed(0);
    EscSetSpeed2(0);

    double measuredAngles = 0.0;
    double angleRadians = 0.0;
    Init();
    PID pid;
    PID_Init(&pid);

    volatile uint8 buffer[5]={0xAA};
    volatile uint16 distance=0;

	Pixy2GetVectors(&PixyVectors);
	DisplayVectors(&PixyVectors);


    for(;;)
	{
//    	Uart_SyncSend(0,buffer,5,100000);
//    	Uart_SyncReceive(0,buffer,5,100000);
//    	distance = (buffer[2] - '0')*100 + (buffer[3] - '0')*10 + (buffer[4] - '0');
//    	DisplayValue(3U,distance, 4U, 0U);
//    	DisplayRefresh();

		Pixy2GetVectors(&PixyVectors);
		DisplayVectors(&PixyVectors);

		ValidateVectors(&PixyVectors);

		switch (PixyVectors.NumberOfVectors)
		{

			case 1:
			{
				// TODO: Calculeaza avgVect pt 1 vector input
				Pixy2SetLed(0,255,0);
				Dio_WriteChannel(111, 1); // RED
				Dio_WriteChannel(112, 0); // GREEN
				Dio_WriteChannel(96, 1);  // BLUE

				averageVector = GetVector2(&PixyVectors.Vectors[0]);

				temp = PixyVectors.Vectors[0];

				break;
			}

			case 2: // Pentru 2 vectori
				{
					Vector2 v0 = GetVector2(&PixyVectors.Vectors[0]);
					Vector2 v1 = GetVector2(&PixyVectors.Vectors[1]);


					if (isIntersection(&v0, &v1))
					{
						DisplayValue(3U,111,4U,0U);
						DisplayRefresh();
						averageVector = GetVector2(&PixyVectors.Vectors[0]);
					}
					else
					{
						averageVector = Average(&v0, &v1);
					}
//					// cazul in care se pastreaza aceeasi 2 vectori tot timpul
//					if ( index0 == PixyVectors.Vectors[0].VectorIndex  && index1 == PixyVectors.Vectors[1].VectorIndex)
//					{
//						Vector2 v0 = GetVector2(&PixyVectors.Vectors[0]);
//						Vector2 v1 = GetVector2(&PixyVectors.Vectors[1]);
//						averageVector = Average(&v0, &v1);
//					}
//					else  // cazul in care sunt la intersectie , si vreau sa aleg doar 1 vector
//					{
//						if(index0 == PixyVectors.Vectors[0].VectorIndex)
//						{
//							averageVector = GetVector2(&PixyVectors.Vectors[0]);
//						}
//						else
//						{
//							averageVector = GetVector2(&PixyVectors.Vectors[1]);
//						}
//
//					}


					// TEMP START
					temp.x0=PixyVectors.Vectors[0].x0 / 2.0 + PixyVectors.Vectors[1].x0 / 2.0;
					temp.y0=PixyVectors.Vectors[0].y0 / 2.0 + PixyVectors.Vectors[1].y0 / 2.0;
					temp.x1=PixyVectors.Vectors[0].x1 / 2.0 + PixyVectors.Vectors[1].x1 / 2.0;
					temp.y1=PixyVectors.Vectors[0].y1 / 2.0 + PixyVectors.Vectors[1].y1 / 2.0;

					// TEMP END


//					Pixy2SetLed(0,0,255);
//					Dio_WriteChannel(111, 1); // RED
//					Dio_WriteChannel(112, 1); // GREEN
//					Dio_WriteChannel(96, 0);  // BLUE


					break;
				}
			default:
			{
//				Pixy2SetLed(255,0,0);
//				Dio_WriteChannel(111, 0); // RED
//				Dio_WriteChannel(112, 1); // GREEN
//				Dio_WriteChannel(96, 1);  // BLUE
			}
		}

		Normalize(&averageVector);

		//direction = ComputeDirection(&averageVector.point);
		measuredAngles = acos(-averageVector.point.y);
		//angleRadians = PID_Compute(&pid, measuredAngles);
		//direction = ComputeDirection(&averageVector.point ,angleRadians);
		direction = ComputeDirection(&averageVector.point ,measuredAngles);

		speed = ComputeSpeed(direction);

		DisplayValue(1U, direction, 4U, 0U);
		// TEMP START 2
		DisplayVector(NormalizePixyVector(temp));
		// TEMP END 2
		DisplayRefresh();



		Steer(direction);
//		if( distance < 20)
//		{
//			speed=0;
//		}
		EscSetSpeed(speed);
		EscSetSpeed2(speed);


	}
}
#ifdef __cplusplus
}
#endif

/** @} */
