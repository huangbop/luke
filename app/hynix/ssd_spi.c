/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**----------------------------------------File Information----------------------------------------------
** File Name             : Ssd_spi.c
** File Version          : V1.0
** File Creator          : Qin Zhi
** File Create Data      : 2012-11-07
** File Description      : SPI
*******************************************************************************************************/
#include "HEAD.H"
#define SPI_CMD_WRENABLE      0x06
#define SPI_CMD_WRDISABLE     0x04
#define SPI_CMD_RDSTATUS      0x05
#define SPI_CMD_WRSTATUS      0x01
#define SPI_CMD_ERASESCT      0xD8
#define SPI_CMD_WRSECTOR      0x02
#define SPI_CMD_RDSECTOR      0x0B
#define SPI_CMD_RDIDCODE      0x9F

#define SPI_SEC_SZ			0x10000//64K
#define SPI_SEC_SZ_BIT		16
INT8U ID[3];
void InitSPI(void)
{
  //rSFRS.serMemCntrl1 = 0x1f;
//  WRITE PROTECT TABLE  //
//  SRP (R) TB  BP2 BP1 BP0 WEL   BUSY  PORTION  VELUE
//  1   0   X   0   0   0   1->0    0   NONE     0x80
//  1   0   0   0   0   1   1->0    0   UP 1/8   0x84
//  1   0   0   0   1   0   1->0    0   UP 1/4   0x88
//  1   0   0   0   1   1   1->0    0   UP 1/2   0x8C
//  1   0   1   0   0   1   1->0    0   LO 1/8   0xA4
//  1   0   1   0   1   0   1->0    0   LO 1/4   0xA8
//  1   0   1   0   1   1   1->0    0   LO 1/2   0xAC
//  1   0   X   1   X   X   1->0    0   ALL      0x90
  INT8U tStatus;
  do
  {
    SPI_WriteStatus(0x92);
    tStatus = SPI_ReadStatus();
  }
  while(tStatus != 0x90);
  
}

INT8U SPI_ReadData(void)
{
  INT8U rval;
  
  while(!(rSFRS.serMemCntrl0 & 0x02));
  rSFRS.serMemDataOut = 0;
  
  while(!(rSFRS.serMemCntrl0 & 0x02));
  rval = rSFRS.serMemDataIn;

  while(!(rSFRS.serMemCntrl0 & 0x02));
  rSFRS.serMemCntrl0 =1 ;
  return rval;  
}

void SPI_WriteData(INT8U WData)
{

  while(!(rSFRS.serMemCntrl0 & 0x02));
  rSFRS.serMemDataOut = WData;

 
  while(!(rSFRS.serMemCntrl0 & 0x02));

}

void SPI_EnWriteOp(INT8U OpCode)
{
  rSFRS.serMemCntrl0 = 1;
  if(OpCode)
  {
    SPI_WriteData(SPI_CMD_WRENABLE);
  }
  else
  {
    SPI_WriteData(SPI_CMD_WRDISABLE);
  }
  rSFRS.serMemCntrl0 = 0;
}

void SPI_PollIdle(void)
{
   INT8U tStatus;

   rSFRS.serMemCntrl0 = 1;

   SPI_WriteData(SPI_CMD_RDSTATUS);
   do
   {
     tStatus = SPI_ReadData();
   }while((tStatus & 0x01) == 0x01);
   rSFRS.serMemCntrl0 = 0;
}

#if 1
void SPI_ReadID(void)
{ 
  while(!(rSFRS.serMemCntrl0 & 0x02));
 // rSFRS.serMemCntrl0 = 1;
  
  SPI_WriteData(SPI_CMD_RDIDCODE);

  ID[0] = SPI_ReadData();
  ID[1] = SPI_ReadData();
  ID[2] = SPI_ReadData();

  while(!(rSFRS.serMemCntrl0 & 0x02));
  rSFRS.serMemCntrl0 = 0;
}


void SPI_EraseWall(void)
{
   SPI_EnWriteOp(TRUE);
   rSFRS.serMemCntrl0 = 1;
   SPI_WriteData(0xC7);
   rSFRS.serMemCntrl0 = 0;
   SPI_PollIdle( );
   SPI_EnWriteOp(FALSE);
}
#endif

INT8U SPI_ReadStatus(void)
{
  INT8U tStatus;
  rSFRS.serMemCntrl0 = 1;
  SPI_WriteData(SPI_CMD_RDSTATUS);
  tStatus = SPI_ReadData();
  rSFRS.serMemCntrl0 = 0;
  return (tStatus);
}

void SPI_WriteStatus(INT8U data)
{
  SPI_EnWriteOp(TRUE);
  rSFRS.serMemCntrl0 = 1;
  SPI_WriteData(SPI_CMD_WRSTATUS);
  SPI_WriteData(data);  
  rSFRS.serMemCntrl0 = 0;
  SPI_PollIdle( );
  SPI_EnWriteOp(FALSE);
}

void SPI_Erase(INT8U Sector_address)
{
   SPI_EnWriteOp(TRUE);
  rSFRS.serMemCntrl0 = 1;
   SPI_WriteData(SPI_CMD_ERASESCT);
   SPI_WriteData(Sector_address);
   SPI_WriteData(0x00);
   SPI_WriteData(0x00);
  rSFRS.serMemCntrl0 = 0;
   SPI_PollIdle( );
   SPI_EnWriteOp(FALSE);
}

void SPI_Write(INT8U Sector_address, INT32U RamLoc)
{
   INT16U page_select, byte_select;
   INT8U ramdata;

   for(page_select = 0; page_select < 256; page_select++)   
   {
     SPI_EnWriteOp(TRUE);   
	  rSFRS.serMemCntrl0 = 1;	 
     SPI_WriteData(SPI_CMD_WRSECTOR);
     SPI_WriteData(Sector_address);
     SPI_WriteData(page_select);
     SPI_WriteData(0x00);  
	 for (byte_select= 0; byte_select < 256; byte_select++)
	 {
	   ramdata = IO_REG08(RamLoc);
	   RamLoc ++;
	   SPI_WriteData(ramdata); 
	 }
     rSFRS.serMemCntrl0 = 0;	 
     SPI_PollIdle( );     
	 SPI_EnWriteOp(FALSE);	 
   }

}



void SPI_READ(INT8U Sector_address, INT32U RamLoc)
{
   INT32U byte_select;
   INT8U ramdata;
   rSFRS.serMemCntrl0 = 1;
   SPI_WriteData(SPI_CMD_RDSECTOR);
   SPI_WriteData(Sector_address);
   SPI_WriteData(0x00);
   SPI_WriteData(0x00);
   SPI_WriteData(0xAA);

   for (byte_select= 0; byte_select < 65536; byte_select++)
   {
	 ramdata = SPI_ReadData( );
	 IO_REG08(RamLoc) = ramdata;
	 RamLoc ++;
   }
  rSFRS.serMemCntrl0 = 0;   
}

void SPI_PollDev(void)
{
  INT8U tStatus;
  do
  {
    SPI_WriteStatus(0x00);
	tStatus = SPI_ReadStatus( );
  }
  while(tStatus != 0x00);
}

void  TestSPI()
{
	SPI_EraseWall();
	SPI_Write(0, 0x05FFF000);
	DBG_FillDDR(DBG_DDR_DATA_ADDR, PAGE_SIZE, 0xff);
	SPI_READ(0,DBG_DDR_DATA_ADDR);
	//SPI_ReadID();
}



/*******************************************************************************************************
*                            End Of File
 ********************************************************************************************************/
