#include "angleFiring.h"

uint16_t DMA_Buffer1[16] ;


void convertFiringPercentageToTimes(float pulse,int *negativeHalf, int *positiveHalf)
{
	int pulseWidth = (int)(100-((pulse / 100) * 50));
	*negativeHalf = (int)pulseWidth;
	*positiveHalf = (int)pulseWidth-50;
}

void getFiringTimesAndCopyIntoBuffer(int *negativeHalf, int *positiveHalf)
{
	static int x=0;
	int y=0,secNegPulse=0,secPosPulse=0;

	//Compute for the HI to LO pulse of the OC
	if(*negativeHalf + COMPENSATE_DELAY >= (100-COMPENSATE_DELAY)){
		if(*negativeHalf + COMPENSATE_DELAY >= 100)
			*negativeHalf = 500;
		else
			secNegPulse=100;
	}
	else if(*negativeHalf + COMPENSATE_DELAY <= 53){
		secNegPulse=MAX_NEG_TIME;
	}
	else
		secNegPulse = *negativeHalf + COMPENSATE_DELAY + 2;

	if(*positiveHalf+ COMPENSATE_DELAY >=(50-COMPENSATE_DELAY)){
		if(*positiveHalf + COMPENSATE_DELAY >= 50)
			*positiveHalf = 500;
		else
			secPosPulse=50;
	}
	else if(*positiveHalf + COMPENSATE_DELAY <= 2){
		secPosPulse= MAX_POS_TIME;
	}
	else
		secPosPulse = *positiveHalf+ COMPENSATE_DELAY + 2;
	//End of computation

	if(x==8)
		x=0;
	while(y!=4)
	{
		DMA_Buffer1[x]= *negativeHalf + COMPENSATE_DELAY;
		DMA_Buffer1[x+1]= secNegPulse;
		DMA_Buffer1[x+2]= *positiveHalf + COMPENSATE_DELAY;
		DMA_Buffer1[x+3]= secPosPulse;
		x+=4;
		y+=4;
	}
}
