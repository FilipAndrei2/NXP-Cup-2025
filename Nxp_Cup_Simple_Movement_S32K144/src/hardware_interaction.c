#include <stdbool.h>
#include "hardware_interaction.h"
#include "speed.h"

volatile float distance = 0.0f;
volatile uint8 terminatedFlag = 1;
volatile uint16 time = 0;
volatile Option_type_potentiometru option = DISPLAY_ON;
volatile _Bool PL;
volatile _Bool displayOn = true;

void Init(void)
{
	DriversInit();
	//Gpt_StartTimer(2,8000); // *48000 for x ms  // 8000 for 1ms
	//Gpt_EnableNotification(2);
	//3100 , 2350 , 2600
	ServoInit(1U, 3200U, 2100U, 2650U);
	SteerStraight();
	EscInit(0U,5U, 1638U, 2457U, 3276U);
	DisplayInit(0U, 1);
	Pixy2Init(0x54, 0x55, 0U);
	PL = false;
}

void DisplayVectors(DetectedVectors* PixyVectors)
{
	//DisplayClear();

	DisplayValue(0U, PixyVectors->NumberOfVectors, 3U, 0U);
	for(uint8 i= 0; i < PixyVectors->NumberOfVectors; ++i)
	{
		DisplayVector(NormalizePixyVector(PixyVectors->Vectors[i]));
	}
	//DisplayRefresh();
}



int GetSteeringValueFromRadians(double angleRadians)
{
	// TODO: IMPLEMENTARE
	// Step 1: Saturam unghiul in rad in interavlul [pi/4, 3*pi/4]
	return 1;
}

void One_milisecond_callback(void) // se apeleaza singura o data la 1ms
{
		time++;
		Dio_WriteChannel(111, 1); // RED
		Dio_WriteChannel(111, 0); // RED
}

void IT_BTN0(void){
	if (option == MAX_SPEED_OPTION)
	{
		option = DISPLAY_ON;
	} else option++;
}


void IT_BTN1(void){
	PL = !PL;
	if (PL) switch (option) {
			case MIN_SPEED_OPTION: MinSpeed(); break;
			case MED_SPEED_OPTION: MedSpeed(); break;
			case MAX_SPEED_OPTION: MaxSpeed(); break;
			case DISPLAY_ON: displayOn = !displayOn; break;
		}
}

void IT_DISTANCE(void){
	if (Dio_ReadChannel(11) == 1)
	{
		time = 0;
		// pornesc timer
		Gpt_StartTimer(2,8000); // *48000 for x ms  // 8000 for 1ms
		Gpt_EnableNotification(2);
	} else {
		// se opreste timer
		Gpt_StopTimer(2);

		Gpt_ValueType numberOfTicks = Gpt_GetTimeElapsed(2);
		float numberOfTicksInMs = numberOfTicks / 8000.0;
		float timeElapsed = time + numberOfTicksInMs;
		distance = timeElapsed * 17;

		terminatedFlag = 1;
	}
}

void ChangeLedColor(_Bool r, _Bool g, _Bool b) {
		Dio_WriteChannel(111, r); // RED
		Dio_WriteChannel(112, g); // GREEN
		Dio_WriteChannel(96, b);  // BLUE
}
