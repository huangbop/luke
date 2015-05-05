/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_DATAXFER_H
#define SSD_DATAXFER_H

void mBfrLLcurrLink ( mUINT_NATIVE segNum, mUINT_NATIVE currLink );
void mBfrSegAdrsOffsetInit(mUINT_NATIVE segNum, mUINT_NATIVE offset);
void mBfrHostSegSecCntInit(mUINT_NATIVE segNum, mUINT_NATIVE value);
void CommandExec(void);
void CommandXfer(void);
void CommandFin(void);
#endif 

/*******************************************************************************************************
End Of File
 ********************************************************************************************************/
