#include "s3c24x0.h"
#include "ucos_ii.h"
#include "stdint.h"


void s4_push()
{

}


void OS_CPU_ExceptHndlr(uint32_t type)
{
    int offset;

    ClearPending(1 << offset);

    if (type == OS_CPU_ARM_EXCEPT_IRQ)
    {

        offset = INTOFFSET;

        switch (offset) {
        case 2:			/* S4 pushed */
            s4_push();
            break;
        case 10:		/* timer0 */

            break;
        default:
            break;
        }

    }

}
