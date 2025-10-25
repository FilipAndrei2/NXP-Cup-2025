#ifndef __PID__
#define __PID__


typedef
struct
{
	float KI ;
	float KP ;
	float integral;


} PID;

void PID_Init(PID *pid);
float PID_Compute(PID* pid, float angleRadians );

#endif // __PID__
