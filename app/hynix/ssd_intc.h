/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_INTC_H
#define SSD_INTC_H

//The Function in Startup.s
void OS_ENTER_CRITICAL(void);
void OS_EXIT_CRITICAL(void);
void sysCPUSysModeEnaIRQ(void);
void sysCPUSysModeEnaFIQ(void);
void sysCPUSysModeDisIntr(void);
void sysCPUSysModeEnaIntr(void);

void InitIntc(void);
#endif

/*******************************************************************************************************
                                            End Of File
********************************************************************************************************/
