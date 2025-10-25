#include "PID.h"

void PID_Init(PID *pid)
{
	pid->integral = 0.0;
	pid->KI = 0.443993793011633;
	pid->KP = 0.830488946587019;

}

float PID_Compute(PID* pid, float angleRadians)
{
	pid->integral += angleRadians;

	return pid->KP * (-angleRadians) + pid->KI * pid->integral;
}
