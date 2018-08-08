#ifndef _ANGLEFIRING_H
#define _ANGLEFIRING_H
#include "stdint.h"
extern uint16_t DMA_Buffer1[16] ;

#define MAX_POS_TIME		5
#define MAX_NEG_TIME		55
#define COMPENSATE_DELAY 	3
void convertFiringPercentageToTimes(float pulse,int *negativeHalf, int *positiveHalf);
void getFiringTimesAndCopyIntoBuffer(int *negativeHalf, int *positiveHalf);
#endif // _ANGLEFIRING_H
