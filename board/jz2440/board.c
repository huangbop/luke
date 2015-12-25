#include "board.h"


void clock_init(void);
void uart_init(void);
void key_init(void);
void timer_init(void);
void mmu_init(void);


void board_init(void)
{
    clock_init();

    uart_init();

    key_init();

    timer_init();

    mmu_init();
}
