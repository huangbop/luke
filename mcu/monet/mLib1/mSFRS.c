// =======        test example     ============================================
//                                                                           
//     Copyright (c) Marvell Corporation 2000-2009  -  All rights reserved     
//                                                                           
//  This computer program contains confidential and proprietary information, 
//  and  may NOT  be reproduced or transmitted, in whole or in part,  in any 
//  form,  or by any means electronic, mechanical, photo-optical, or  other- 
//  wise, and  may NOT  be translated  into  another  language  without  the 
//  express written permission from Marvell Corporation.                     
//                                                                           
// ============================================================================
// =      C O M P A N Y      P R O P R I E T A R Y      M A T E R I A L       =
// ============================================================================


/*----------------------------------------------------------------------------
 Include files:
 ---------------------------------------------------------------------------*/
#define   INSTANTIATE_SYMBOLS_SPEC_FUNC_REGS
#include "mSFRS.h"
#include "mREGS.h"

/*******************************************************************
*
*  NAME:        mCPUintrEnInit
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 value
*
*  DESCRIPTION: set interrupt enable for corresponding core
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mCPUintrEnInit (mUINT_16 value)
{
    rCPU.cpuIntrEnable.all = value;
}

/*******************************************************************
*
*  NAME:   	    mCPUintrEn
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 value
*
*  DESCRIPTION: unmask interrupt enable for corresponding core
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mCPUintrEn (mUINT_16 value)
{
    rCPU.cpuIntrEnable.all |= value;
}

/*******************************************************************
*
*  NAME:        mCPUintrDis
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 value
*
*  DESCRIPTION: mask interrupt enable for corresponding core
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mCPUintrDis (mUINT_16 value)
{
    rCPU.cpuIntrEnable.all &= ~value;
}

/*******************************************************************
*
*  NAME:        mCPUintrStatus
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return the contents of the interrupt
*               status register of corresponding core.
*
*  RETURNS:     type mUINT_16 interrupt status
*
********************************************************************/
INLINE mUINT_16 mCPUintrStatus(void)
{
    return rCPU.cpuIntrStatus.all;
}

/*******************************************************************
*
*  NAME:        mCPUClrIntrStatus
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to clear the interrupt
*               status register of corresponding core.
*
*  RETURNS:     void
*
********************************************************************/
INLINE void mCPUClrIntrStatus(mUINT_16 bitMask)
{
    rCPU.cpuIntrStatus.all = bitMask;
}

/*******************************************************************
*
*  NAME:        mSFRintrEnInit
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 value
*
*  DESCRIPTION: set peri interrupt enable for corresponding core
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRintrEnInit (mUINT_16 value)
{
    rCPU.periIntrEn.all = value;
}

/*******************************************************************
*
*  NAME:   	    mSFRintrEn
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 value
*
*  DESCRIPTION: unmask peri interrupt enable for corresponding core
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRintrEn (mUINT_16 value)
{
    rCPU.periIntrEn.all |= value;
}

/*******************************************************************
*
*  NAME:        mSFRintrDis
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 value
*
*  DESCRIPTION: mask peri interrupt enable for corresponding core
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRintrDis (mUINT_16 value)
{
    rCPU.periIntrEn.all &= ~value;
}

/*******************************************************************
*
*  NAME:        mSFRintrStatusClr
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  mUINT_16 intSource
*
*  DESCRIPTION: API function to load the peri interrupt status
*               register of corresponding core with the given value.
*               Loading a '1' to any bit position will clear the
*               corresponding interrupt status.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRintrStatusClr(mUINT_16 intSource)
{
    rCPU.periIntrStatus.all = intSource;
}

/*******************************************************************
*
*  NAME:        mSFRintrStatus
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return the contents of the peri 
*               interrupt status register of corresponding core.
*
*  RETURNS:     type mUINT_16 interrupt status
*
********************************************************************/
INLINE mUINT_16 mSFRintrStatus(void)
{
    return rCPU.periIntrStatus.all;
}

/*******************************************************************
*
*  NAME:        mCPUintrEnable
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return the contents of the interrupt
*               enable of corresponding core.
*
*  RETURNS:     type mUINT_16 interrupt enable
*
********************************************************************/
INLINE mUINT_16 mCPUintrEnable(void)
{
    return rCPU.cpuIntrEnable.all;
}

/*******************************************************************
*
*  NAME:        mSFRinitcpuIntrCntl1
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to init cpuIntrCntl1
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRinitcpuIntrCntl1(void)
{
    rSFRS.cpuIntrCntl1.all = 0x4001;
}


/*******************************************************************
*
*  NAME:        mSFRinitcpuIntrCntl2
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to init cpuIntrCntl2
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRinitcpuIntrCntl2(void)
{
    // FOR SSW: Basically, allow only SCPU wr interrupt to go to HCPU IRQ.
    //    rSFRS.cpuIntrCntl2 = 0x0002;  KEN allow HCPU to wr interrupt to SCPU
    // FOR NV: allow HCPU to wr IPC cmd to generate FIQ to SCPU 
    rSFRS.cpuIntrCntl2 = 0x0102;  // KEN CPU0 kicks CPU1 with a FIQ and CPU 1 kick CPU 0 with an IRQ 
}





/*******************************************************************
*
*  NAME:        mSFRfiq0Sel
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to set FIQ select bits in interrupt
*               control register for core 0
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRfiq0Sel (mUINT_8 value)
{
    rSFRS.cpuIntrCntl0.bits.fiq0Select = value;
}

/*******************************************************************
*
*  NAME:        mSFRfiq1Sel
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to set FIQ select bits in interrupt
*               control register for core 1
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRfiq1Sel (mUINT_8 value)
{
    rSFRS.cpuIntrCntl0.bits.fiq1Select = value;
}

/*******************************************************************
*
*  NAME:        mSFRirq0Sel
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to set IRQ select bits in interrupt
*               control register for core 0
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRirq0Sel (mUINT_8 value)
{
    rSFRS.cpuIntrCntl0.bits.irq0Select = value;
}

/*******************************************************************
*
*  NAME:        mSFRirq1Sel
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to set IRQ select bits in interrupt
*               control register for core 1
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRirq1Sel (mUINT_8 value)
{
    rSFRS.cpuIntrCntl0.bits.irq1Select = value;
}

/*******************************************************************
*
*  NAME:        mSFRlatchSvoIntr0
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to enable interrupt latching for the
*               servo on CPU 0.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRlatchSvoIntr0 (mUINT_8 value)
{
    rSFRS.cpuIntrCntl1.bits.C0SrvIntLatEn = value;
}





/*******************************************************************
*
*  NAME:        mSFRgenerateSwIrq()
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: Generate Soft IRQ. This is done by setting swIrq bit
*               in single core architecture. 
*               For dual core architecture, this has to be simulated
*               by using mailbox command interrupt until the swIrq
*               becomes routable in the next version of Solaris. HB.
*
*               This routine is supposed to be called from core 1 only
*               if (mDUAL_CORE_SUPPORT == mENABLE) and 
*               (mDUAL_CORE_FW_ARCH == mSINGLE_CORE_EMUL).
*
*               In any other options, this routine is supposed to be 
*               called from core 0 only
*
*  PARAMETERS:  None
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRgenerateSwIrq(void)
{
    rCPU.intrControl.bits.swIrq = 1;
}

/*******************************************************************
*
*  NAME:        mSFRcheckSwIrq()
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: See if Soft IRQ is pending. This is done by checking
*               the swIrq bit in single core architecture. 
*               For dual core architecture, this has to be simulated
*               by using mailbox command interrupt until the swIrq
*               becomes routable in the next version of Solaris. HB.
*
*               This routine is supposed to be called from core 0 only.
*
*  PARAMETERS:  None
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mSFRcheckSwIrq(void)
{
    return (rCPU.intrControl.bits.swIrq);
}

/*******************************************************************
*
*  NAME:        mSFRclrSwIrq()
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: Clear pending Soft IRQ. This is done by clearing
*               the swIrq bit in single core architecture. 
*               For dual core architecture, this has to be simulated
*               by using mailbox command interrupt until the swIrq
*               becomes routable in the next version of Solaris. HB.
*
*               This routine is supposed to be called from core 0 only.
*
*  PARAMETERS:  None
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRclrSwIrq(void)
{
    rCPU.intrControl.bits.swIrq = 0;
}


#if (mDUAL_CORE_SUPPORT == mENABLE)
  #if (mDUAL_CORE_FW_ARCH == mSINGLE_CORE_EMUL)
/*******************************************************************
*
*  NAME:        mSFRSendServoMailBoxCmd
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: Send Mail Box command (from core 1 to core 0)
*
*               This routine is supposed to be called from core 1 only.
*
*  PARAMETERS:  32 bit command code.
*
*  RETURNS:     None
*
********************************************************************/
void mSFRSendServoMailBoxCmd(mUINT_16 CmdOPCode, mUINT_16 CmdParameter)
{
    rSFRS.SIPCCommand0Lo = CmdParameter;
    rSFRS.SIPCCommand0Hi = CmdOPCode;
}

/*******************************************************************
*
*  NAME:        mSFRcheckServoMailbox()
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: See if there is new servo mailbox command.
*               This routine is supposed to be called from core 0 only.
*
*  PARAMETERS:  None
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mSFRcheckServoMailbox(void)
{
    // Check mailbox interrupt
    if (rCPU.periIntrStatus.bits.IPCCmdWritten)
    {
        if ((rSFRS.SIPCCommand0Lo != 0) || (rSFRS.SIPCCommand0Hi != 0))
        {
            return mTRUE;
        }
    }
    return mFALSE;
}

/*******************************************************************
*
*  NAME:        mSFRSendMailBoxCmd
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: Send Mail Box command (from core 0 to core 1)
*
*               This routine is supposed to be called from core 0 only.
*
*  PARAMETERS:  pCmd[] is a 6 word array matching Ra030 to Ra03a.
*
*  RETURNS:     None
*
********************************************************************/
void mSFRSendMailBoxCmd(mUINT_16 *pCmd)
{
    rSFRS.HIPCCommand0Lo = *pCmd++;
    rSFRS.HIPCCommand0Hi = *pCmd++;
    rSFRS.HIPCCommand1Lo = *pCmd++;
    rSFRS.HIPCCommand1Hi = *pCmd++;
    rSFRS.HIPCCommand2Lo = *pCmd++;
    rSFRS.HIPCCommand2Hi = *pCmd;
}
/*******************************************************************
*
*  NAME:        mSFRSendHIPCCmd2Hi    // KEN
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: Write IPC CMD2 Hi command 
*
*               This routine is supposed to be called from core 0 only.
*
*  PARAMETERS:  cmdValue to Ra03a.
*
*  RETURNS:     None
*
********************************************************************/
void mSFRSendHIPCCmd2Hi(mUINT_16 cmdValue)
{
    rSFRS.HIPCCommand2Hi = cmdValue;
}

/*******************************************************************
*
*  NAME:        mSFRcheckCore1Mailbox()
*
*  FILENAME:    mSFRS.c
*
*  DESCRIPTION: See if there is new servo mailbox command.
*               This routine is supposed to be called from core 0 only.
*
*  PARAMETERS:  None
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mSFRcheckCore1Mailbox(void)
{
    // Check mailbox interrupt
    if (rCPU.periIntrStatus.bits.IPCCmdWritten)
    {
        if ((rSFRS.SIPCCommand0Lo != 0) || (rSFRS.SIPCCommand0Hi != 0))
        {
            return mTRUE;
        }
    }
    return mFALSE;
}

  #endif // (mDUAL_CORE_FW_ARCH == mSINGLE_CORE_EMUL)
#endif // (mDUAL_CORE_SUPPORT == mENABLE)
