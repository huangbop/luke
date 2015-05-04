#include "s3c24x0.h"


void key_init()
{
	/*
	 * GPF0 - EINT0 - S2
	 * GPF2 - EINT2 - S3
	 */
	GPFCON &= ~0x33;
	GPFCON |= 0x22;
	
	INTMSK &= ~((1 << 0) | (1 << 2));
}
