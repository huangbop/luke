/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**----------------------------------------File Information----------------------------------------------
** File Name             : Ssd_SPI.h
** File Version          : V1.0
** File Creator          : Qin Zhi
** File Create Data      : 2012-11-07
** File Description      : SPI
**
**----------------------------------------File History--------------------------------------------------
** Modified Man          : 
** Modified Date         : 
** Modified Info         : 
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

#ifndef SSD_SPI_H
#define SSD_SPI_H

void  InitSPI(void);
INT8U SPI_ReadData(void);
void  SPI_WriteData(INT8U WData);
void  SPI_EnWriteOp(INT8U OpCode);
void  SPI_PollIdle(void);
INT8U SPI_ReadStatus(void);
void  SPI_WriteStatus(INT8U data);
void  SPI_Erase(INT8U Sector_address);
void  SPI_Write(INT8U Sector_address, INT32U RamLoc);
void  SPI_READ(INT8U Sector_address, INT32U RamLoc);
void  SPI_PollDev(void);
void  SPI_EraseWall(void);
void  SPI_ReadID(void);
void  TestSPI();
void  TestSPI1();

#endif 
/*****************************************************************************************************
**                                  End of File                                                       
 ******************************************************************************************************/
