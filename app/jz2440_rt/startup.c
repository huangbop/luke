#include "ucos_ii.h"


int main()
{
	board_init();

  OSInit();

  OSStart();

  while (1)
      ;

	return 0;
}
