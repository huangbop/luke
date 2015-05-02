

int rt_hw_interrupt_disable(void);



int main()
{
	rt_hw_interrupt_disable();
	
	board_init();

	rt_show_version();

	return 0;
}
