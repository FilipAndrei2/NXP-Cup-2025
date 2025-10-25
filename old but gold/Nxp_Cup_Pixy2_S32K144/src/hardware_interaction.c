#include "hardware_interaction.h"


void Init(void)
{
	DriversInit();
	Gpt_StartTimer(2,8000); // *48000 for x ms  // 8000 for 1ms
	Gpt_EnableNotification(2);
	//3100 , 2350 , 2600
	ServoInit(1U, 3200U, 2100U, 2650U);
	SteerStraight();
	EscInit(0U,5U, 1638U, 2457U, 3276U);
	DisplayInit(0U, 1);
	Pixy2Init(0x54, 0U);

}

void DisplayVectors(DetectedVectors* PixyVectors)
{
	DisplayClear();

	DisplayValue(0U, PixyVectors->NumberOfVectors, 3U, 0U);
	for(uint8 i= 0; i < PixyVectors->NumberOfVectors; ++i)
	{
		DisplayVector(NormalizePixyVector(PixyVectors->Vectors[i]));
	}
	DisplayRefresh();
}



int GetSteeringValueFromRadians(double angleRadians)
{
	// TODO: IMPLEMENTARE
	// Step 1: Saturam unghiul in rad in interavlul [pi/4, 3*pi/4]
	return 1;
}

void One_milisecond_callback(void) // se apeleaza singura o data la 1ms
{
		Dio_WriteChannel(111, 1); // RED
		Dio_WriteChannel(111, 0); // RED
}
