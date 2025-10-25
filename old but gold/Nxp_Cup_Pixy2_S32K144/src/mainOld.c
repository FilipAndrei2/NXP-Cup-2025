//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
///*==================================================================================================
// *                                        INCLUDE FILES
// * 1) system and project includes
// * 2) needed interfaces from external units
// * 3) internal and external interfaces from this unit
//==================================================================================================*/
//#include <math.h>
//
//#include "consts.h"
//#include "hardware_interaction.h"
///*==================================================================================================
// *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
//==================================================================================================*/
//
///*==================================================================================================
// *                                       LOCAL MACROS
//==================================================================================================*/
//
///*==================================================================================================
// *                                      LOCAL CONSTANTS
//==================================================================================================*/
///*==================================================================================================
// *                                      LOCAL VARIABLES
//==================================================================================================*/
//
///*==================================================================================================
// *                                      GLOBAL CONSTANTS
//==================================================================================================*/
//
///*==================================================================================================
// *                                      GLOBAL VARIABLES
//==================================================================================================*/
//
///*==================================================================================================
// *                                   LOCAL FUNCTION PROTOTYPES
//==================================================================================================*/
//
///*==================================================================================================
// *                                       LOCAL FUNCTIONS
//==================================================================================================*/
//
///*==================================================================================================
// *                                       GLOBAL FUNCTIONS
//==================================================================================================*/
///**
// * @brief        Main function of the example
// * @details      Initializes the used drivers, hbridge, display, Pixy and servo.  The code
// *                  tries to keep the car between the two black lines using a Pixy2 camera.
// */
//
//
//
//
//int main(void)
//{
//    volatile uint16 Delay = 10000;
//    DetectedVectors PixyVectors;
//
//	Init();
//
//    /*while(1){
//        double m0 = 0, m1 = 0;
//        Pixy2GetVectors(&PixyVectors);
//        if(PixyVectors.NumberOfVectors>=2){
//            double x0 = PixyVectors.Vectors[0].x0;
//            double x1 = PixyVe	ctors.Vectors[0].x1;
//
//            double y0 = PixyVectors.Vectors[0].y0;
//            double y1 = PixyVectors.Vectors[0].y1;
//
//            double x0_1 = PixyVectors.Vectors[1].x0;
//            double x1_1 = PixyVectors.Vectors[1].x1;
//
//            double y0_1 = PixyVectors.Vectors[1].y0;
//            double y1_1 = PixyVectors.Vectors[1].y1;
//            m0 = (x0 - x1) / (y0-y1);
//            m1 = (x0_1 - x1_1) / (y0_1 - y1_1);
//            Pixy2SetLed(0U,255U,0U);
//            // ACTIV PE 0
//          Dio_WriteChannel(111, 1); // RED
//          Dio_WriteChannel(112, 0); // GREEN
//			Dio_WriteChannel(96, 1);  // BLUE
//        }
//        else if(PixyVectors.NumberOfVectors == 1){
//            double x0 = PixyVectors.Vectors[0].x0;
//            double x1 = PixyVectors.Vectors[0].x1;
//
//            double y0 = PixyVectors.Vectors[0].y0;
//            double y1 = PixyVectors.Vectors[0].y1;
//            m0 = (x0 - x1) / (y0-y1);
//            Pixy2SetLed(255U,0U,0U);
//            Dio_WriteChannel(111, 0); // RED
//            Dio_WriteChannel(112, 1); // GREEN
//			Dio_WriteChannel(96, 1);  // BLUE
//        }
//        CarSteer = (m0  + m1) * 65;
//        EscSetSpeed(50);
//        EscSetSpeed2(50);
//        Steer(-CarSteer);
//        // Display
//			DisplayClear();
//			DisplayValue(0U, PixyVectors.NumberOfVectors, 3U, 0U);
//
//			for(uint8 Index = 0U; Index < PixyVectors.NumberOfVectors; Index++){
//				DisplayVector(NormalizePixyVector(PixyVectors.Vectors[Index]));
//			}
//			DisplayRefresh();
//
//			Delay=10000U;
//			while(Delay){
//				Delay--;
//			}
//    }*/
//
//	// double integrator=0;
//	// double prevErr=0;
//	// double prevAngle=0;
//	// double proportional=0;
//	double out=0;
//	//double ref=0f;
//	// double err=0;
//	double angle=0;
//	Line averageLine;
//	DVector averageVect;
//
//
//
//	while(1)
//	{
//		Pixy2GetVectors(&PixyVectors);
//		DisplayVectors(&PixyVectors);
//
//		switch (PixyVectors.NumberOfVectors)
//		{
//			case 0: // LED = RED
//			{
//				Pixy2SetLed(255, 0, 0);
////				Dio_WriteChannel(111,0); // RED
////				Dio_WriteChannel(112, 1); // GREEN
////				Dio_WriteChannel(96, 1);  // BLUE
//				// TODO: implement
//				break;
//			}
//			case 1: // LED = BLUE
//			{
//				Pixy2SetLed(0, 0, 255);
////				Dio_WriteChannel(111, 1); // RED
////				Dio_WriteChannel(112, 1); // GREEN
////				Dio_WriteChannel(96, 0);  // BLUE
//
//
//				averageLine.A.x = PixyVectors.Vectors[0].x0;
//				averageLine.A.y = PixyVectors.Vectors[0].y0;
//				averageLine.B.x = PixyVectors.Vectors[0].x1;
//				averageLine.B.y = PixyVectors.Vectors[0].y1;
//
//				break;
//			}
//			default:  // >=2 , LED = GREEN
//			{
//				Pixy2SetLed(0, 255, 0);
////				Dio_WriteChannel(111, 1); // RED
////				Dio_WriteChannel(112, 0); // GREEN
////				Dio_WriteChannel(96, 1);  // BLUE
//
//				averageLine.A.x=PixyVectors.Vectors[0].x0 / 2.0 + PixyVectors.Vectors[1].x0 / 2.0;
//				averageLine.A.y=PixyVectors.Vectors[0].y0 / 2.0 + PixyVectors.Vectors[1].y0 / 2.0;
//				averageLine.B.x=PixyVectors.Vectors[0].x1 / 2.0 + PixyVectors.Vectors[1].x1 / 2.0;
//				averageLine.B.y=PixyVectors.Vectors[0].y1 / 2.0 + PixyVectors.Vectors[1].y1 / 2.0;
//
//
//			}
//		}
//
//		averageVect.x=fabs(averageLine.B.x-averageLine.A.x);
//		averageVect.y=fabs(averageLine.B.y-averageLine.A.y);
//
//		// if(PixyVectors.NumberOfVectors>=2)
//		// {
//		//     averageLine.A.x=PixyVectors.Vectors[0].x0 / 2.0 + PixyVectors.Vectors[1].x0 / 2.0;
//		//     averageLine.A.y=PixyVectors.Vectors[0].y0 / 2.0 + PixyVectors.Vectors[1].y0 / 2.0;
//		//     averageLine.B.x=PixyVectors.Vectors[0].x1 / 2.0 + PixyVectors.Vectors[1].x1 / 2.0;
//		//     averageLine.B.y=PixyVectors.Vectors[0].y1 / 2.0 + PixyVectors.Vectors[1].y1 / 2.0;
//
//		//     averageVect.x=fabs(averageLine.B.x-averageLine.A.x);
//		//     averageVect.y=fabs(averageLine.B.y-averageLine.A.y);
//
//		// }
//		// else if(PixyVectors.NumberOfVectors == 1)
//		// {
//		// 	if(PixyVectors.Vectors[0].x1 < PixyVectors.Vectors[0].x0)  // steer --->>>> right
//		// 	{
//		// 		Point Center;
//		// 		Center.x = PixyVectors.Vectors.x0;
//		// 		Center.y = PixyVectors.Vectors
//		// 	}
//		// 	else // sterr <<<<---- left
//		// 	{
//
//		// 	}
//		// }
//		// else {
//		// 	// !!!!!! TO DO !!!!!!!!
//		// 	//steer straight
//		// }
//
//
//		NormalizeVector(&averageVect);
//
//		angle=acos(-averageVect.y);P
//
////            err=-angle;
////            proportional=KP*err;
////            integrator=integrator+0.5f*KI*T*(err+prev_err);
//
//	  //  out=proportional+integrator;
//
//		//Steer(-CONVERT_RADIANS_TO_STEER_INPUT(angle));        // out > 0 ? Steer stanga : Steer dreapta; Se poate sa nu trebuiasca - ul din fata
//		Steer(-(angle*100));
//		EscSetSpeed(60);
//		EscSetSpeed2(60);
//
//	//     prev_err=err;
//	//     prev_angle=angle;
//	// }
//
//	}
//
//
//}
//#ifdef __cplusplus
//}
//#endif
//
///** @} */
