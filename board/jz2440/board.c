#include "board.h"

void board_init(void)
{
	clock_init();
	
	uart_init();

	timer_init();

	
}
