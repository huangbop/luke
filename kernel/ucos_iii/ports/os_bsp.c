#include <os.h>


void  OS_CPU_ExceptHndlr (CPU_INT32U  except_id)
{

    switch (except_id) {
    case OS_CPU_ARM_EXCEPT_IRQ:

        break;
    case OS_CPU_ARM_EXCEPT_FIQ:
    case OS_CPU_ARM_EXCEPT_RESET:
    case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
    case OS_CPU_ARM_EXCEPT_SWI:
    case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
    case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        while (1)
            ;
        break;
    }
}
