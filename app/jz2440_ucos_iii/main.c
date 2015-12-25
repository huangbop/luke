#include "board.h"
#include "os.h"




int main()
{
    OS_ERR err;


    board_init();

    OSInit(&err);

    OSStart(&err);

    while (1)
        ;

    return 0;
}
