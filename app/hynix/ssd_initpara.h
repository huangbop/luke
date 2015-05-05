/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_INITPARA_H
#define SSD_INITPARA_H

#define mBFR_DPD_EN                         mBIT(7)
 #define mK_TO_BYTES               (1024UL)        // 1K
#define mAU_SIZE_IN_K             (4UL)           // each allocation unit - 4K bytes, this is for user data -- logical only.   
                                                    // One AU can occupy more physical space due to ECC and stuff

#define mAU_SIZE                  (mAU_SIZE_IN_K * mK_TO_BYTES)
#define mAU_SIZE_BYTE             (mAU_SIZE_IN_K * mK_TO_BYTES)
  // AU size in terms of 512 byte sector.
#define mAU_SIZE_SECTOR           (mAU_SIZE_BYTE/mSECTOR_SIZE)


#if (mAU_SIZE >= mSECTOR_SIZE)
#define mNV_SECTOR_SIZE_RATIO   (mAU_SIZE/mSECTOR_SIZE)
#else
#define mNV_SECTOR_SIZE_RATIO   ((mSECTOR_SIZE/mAU_SIZE) | (1 << 4))
#endif

extern volatile INT32U mBufferEnd, mDDRSize, firstOOB;
extern mtPARAM_HBI_PAGE             mParamPageHBI;


void mInitHBI (void);
void InitSystem(void);
#endif
/*******************************************************************************************************
                                            End Of File
********************************************************************************************************/
