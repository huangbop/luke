#include "s3c24x0.h"



void uart_init(void)
{
	GPHCON |= 0xa0;

	/* Tx/Rx interrupt mode */
	UCON0 = 0x5;
	/* Baudrate & flow control setting */
	UBRD0 = 26;
	ULCON0 = 0x3;
}


void uart_putc(const char c)
{
	while (!(USTAT0 & 0x2))
		;

	UTXH0 = c;

	if (c == '\n')
		uart_putc('\r');
}

void uart_puts(const char *str)
{
	while (*str) {
		uart_putc(*str);
		str++;
	}
}
