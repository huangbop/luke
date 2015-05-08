#include "mCONDS.h"
#include "mSFRS.h"
#include "mSFRS2.h"
#include "mCLKPWR.h"
#include "mTimer.h"


void board_init(void)
{
	int i;
	
	system_clock_init();

	uart_init();

	
}
