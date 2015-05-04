#include "s3c24x0.h"

extern PCLK;

void timer_init(void)
{
		
	TCFG0  = 99;
	TCFG1  = 0x03;		/* PCLK/100/16 */

	TCNTB0 = (int)(PCLK/100/16/100) - 1; /* one second */
	TCON   |= (1<<1);		     /* update count buf */

	TCON   = 0x09;

//	INTMSK &= ~(1 << 10);	/* Unmask timer0 */

}
