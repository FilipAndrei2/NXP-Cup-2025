#include "distance_senzor.h"

typedef enum{
	BUSSY,
	IDDLE
}Sensor_State;
volatile uint8 distance2;
volatile Sensor_State state = IDDLE;
volatile uint8 buffer[5]={0xAA};
void SenzorUpdate(void)
{
	if(state == IDDLE)
	{
		state=BUSSY;
		Uart_AsyncReceive(0,buffer,5);
	}
	else if(state == BUSSY)
	{
		;
	}
}
void intrerupere_UART(void)
{
//	distance2 = (buffer[2] - '0')*100 + (buffer[3] - '0')*10 + (buffer[4] - '0');
//	state=IDDLE;
}

uint16 getDistance(void){
	return distance2;
}

