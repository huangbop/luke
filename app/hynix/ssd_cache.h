/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_CACHE_H
#define SSD_CACHE_H

#define DDRCPUACCESSBASE               0x50000000
#define CACHESIZE_B                    4096
#define CACHESIZE_S                    (CACHESIZE_B >> 0x09)

//RD Cache 128K ~1M+128K 
#define RDCacheStaDDR_B                0x00020000
#define RDCacheStaDDR_S                (RDCacheStaDDR_B >> 0x09)   
#define RDCacheCnt                     BFR_SSD_RDCNT
//WR Cache 1M+128K ~2M+128K 
#define WRCacheStaDDR_B                0x00120000   
#define WRCacheStaDDR_S                (WRCacheStaDDR_B >> 0x09)
#define WRCacheCnt                     BFR_SSD_WRCNT
//Cache LookUP Table 32M ~32M+64K
#define SIMRAMDISKSIZE                 128*1024*1024
#define CACHE_LOOKUPTBLSIZE            ((SIMRAMDISKSIZE / 4096) * 2)
#define CACHE_LOOKUPTBLADR_B           0x02000000

//Real Data From 64M ~ 64M+128M
#define SIMRAMDISKOFST_B               0x04000000
#define SIMRAMDISKOFST_S               (SIMRAMDISKOFST_B >> 0x09)

#define CACHESTA_IDLE                  0x00
#define CACHESTA_WR                    0x01
#define CACHESTA_RD                    0x02
#define CACHESTA_WRFIN                 0x03
#define CACHESTA_FLUSH                 0x04

typedef struct lpncache_node
{
  INT32U DDRByteAddr;
  INT32U LogPageNum;

  volatile INT8U CacheSta;
}LPNCACHE_NODE;

typedef struct bfrssdparameter
{
  INT32U RDSSDCnt;
  INT32U RDSSDFCPtr;
  INT32U RDSSDHSPtr;
  INT32U RDSSDXferPtr;

  INT32U WRSSDCnt;
  INT32U WRSSDHSPtr;
  INT32U WRSSDFCPtr;  
  INT32U WRSSDXferPtr;
}BFRSSDPARAMETER;



extern LPNCACHE_NODE RdCache[RDCacheCnt];
extern LPNCACHE_NODE WrCache[WRCacheCnt];
extern BFRSSDPARAMETER BfrSSDParam;

INT16U CacheLookUP(INT32U LogicLPN);
void CacheSetTbl(INT32U LogicLPN, INT16U CacheIndex);
BOOLEAN CacheReadOperation(CMDQENTRY *pCmdQEntry);
BOOLEAN CacheWriteOperation(CMDQENTRY *pCmdQEntry);
void mCacheInit(void );

#endif

/*******************************************************************************************************
                                            End Of File
********************************************************************************************************/

