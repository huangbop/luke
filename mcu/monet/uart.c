#include "mSFRS2.h"
#include "mUART.h"

void uart_putc(const char c)
{
	while (!rUART.status.bits.xmitRdy) /* A62C */
		;

	rUART.xmit.bits.data = c; /* A624 */
}

void uart_puts(const char *s)
{
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

int uart_init(void)
{
	rSFRS2.testOutputCntl.rxOutSel = 1;
	rSFRS2.testOutputCntl.txOutSel = 0; /* A828 */

	rSFRS2.ioControlExt.bits.uartDis = 0; 
	rSFRS2.ioControlExt.bits.rxOutputEn = 0; 
	rSFRS2.ioControlExt.bits.txOutputEn = 1; /* A84C */


	rUART.cntrl.all |= (1 << 14) | (1 << 15); /* A628, FIFO reset */
	rUART.baudRate.bits.divisor = (100000000 / 115200) >> 4; /* A630, 100MHz */
	rUART.cntrl.all &= ~((1 << 14) | (1 << 15)); /* A628, FIFO reset */

}
