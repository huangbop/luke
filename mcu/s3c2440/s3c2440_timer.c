#include "s3c24x0.h"

extern PCLK;

void timer_init(void)
{
		
	/* TCFG0  = 99; */
	/* TCFG1  = 0x03;		/\* PCLK/100/16 *\/ */

	/* TCNTB0 = (int)(PCLK/100/16/100) - 1; /\* one second *\/ */
	/* TCON   |= (1<<1);		     /\* update count buf *\/ */

	/* TCON   = 0x09; */

	/* timer4, pre = 15+1 */
	TCFG0 &= 0xffff00ff;
	TCFG0 |= 15 << 8;
	/* all are interrupt mode,set Timer 4 MUX 1/4 */
	TCFG1  &= 0xfff0ffff;
	TCFG1  |= 0x00010000;

	TCNTB4 = (int)(PCLK / (4 *16* 100)) - 1;
	/* manual update */
	TCON = TCON & (~(0x0f<<20)) | (0x02<<20);
	/* install interrupt handler */


    /* start timer4, reload */
	TCON = TCON & (~(0x0f<<20)) | (0x05<<20);
}
