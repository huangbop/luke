/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_CQ_H
#define SSD_CQ_H

#define LBA_LPNNUMMASK                 0xFFFFFFF8
#define LBA_LPNNUMOFST                 0x00000003
#define LBA_LPNOFFMASK                 0x00000007
#define LBA_LPNOFFOFST                 0x00000000
#define LBA_LPNSECSIZE                 0x00000008

#if CFG_FAKECQOP > 0
BOOLEAN FCReadOperation(CMDQENTRY *pCmdQEntry,INT32U LBAAddr, INT32U SecCnt);
BOOLEAN FCWriteOperation(CMDQENTRY *pCmdQEntry,INT32U LBAAddr, INT32U SecCnt);
void FCFlushOperation(CXSBLINK *pCxsbEntry);
void HSReadOperation(CXSBLINK *pCxsbEntry);
#endif

#endif
/*******************************************************************************************************
                                            End Of File
********************************************************************************************************/
