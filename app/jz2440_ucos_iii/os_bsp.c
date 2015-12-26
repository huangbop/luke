#include <os.h>
#include "s3c24x0.h"

void s4_push()
{

}

void  OS_CPU_ExceptHndlr (CPU_INT32U  except_id)
{
    unsigned offset;


    switch (except_id) {

    case OS_CPU_ARM_EXCEPT_IRQ:

        offset = INTOFFSET;
        ClearPending(1 << offset);

        switch (offset) {
        case 2:			/* S4 pushed */
            s4_push();
            break;
        case 10:		/* timer0 */

            break;
        default:
            break;
        }

        break;
    case OS_CPU_ARM_EXCEPT_FIQ:
    case OS_CPU_ARM_EXCEPT_RESET:
    case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
    case OS_CPU_ARM_EXCEPT_SWI:
    case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
    case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        while (1)
            ;                   /* Halt */
    }
}
