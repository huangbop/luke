#include "s3c24x0.h"


unsigned FCLK = 400000000;
unsigned HCLK = 100000000;
unsigned PCLK = 50000000;

void clock_init(void)
{
	LOCKTIME = 0xffffffff;

	/* 12MHz to 400MHz */
	MPLLCON = (0x5c << 12) | (1 << 4) | 1;

	/* Div 1:4:8 */
	CLKDIVN = 0x5;
}
