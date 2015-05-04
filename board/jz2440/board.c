#include "board.h"

void board_init(void)
{
	clock_init();
	
	uart_init();

	key_init();

	timer_init();
	
	mmu_init();
}
