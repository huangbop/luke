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

#ifndef     _mUART_H_INC
  #define   _mUART_H_INC

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MUART
  #define   EXTERN
#else
  #define   EXTERN extern
#endif


typedef union                       // Recv Buffer     
{
      mUINT_16  all;                    
    struct 
    {                                
        mUINT_16  data              : 8;
   
        mUINT_16  rsvd              : 4;
        mUINT_16  overRunErr        : 1; 
        mUINT_16  parityErr         : 1;  
        mUINT_16  framingErr        : 1;  
        mUINT_16  breakDetected     : 1;  
    }bits;                         
} mtUART_RCV_BUFFER;



typedef union                       // Xmit Holding    
{                                   
    mUINT_16  all;                    

    struct 
    {                                
        mUINT_16  data      : 8;
        mUINT_16  rsvd      : 8;

    }bits;                           
}mtUART_XMIT_HOLD;


    /*
    ** UART CONTROL bit masks
    */
    #define mUART_OE_INT_EN             0x0001      // bit: over Run Int En     
    #define mUART_PE_INT_EN             0x0002      // bit: prty Err Int En   
    #define mUART_FE_INT_EN             0x0004      // bit: frame Err Int En  
    #define mUART_BRK_DET_INT_EN        0x0008      // bit: break Detect Int En  
    #define mUART_RX_RDY_INT_EN         0x0010      // bit: rcv Rdy Int En    
    #define mUART_TX_RDY_INT_EN         0x0020      // bit: xmit Rdy Int En   
    #define mUART_TX_EMPTY_INT_EN       0x0040      // bit: xmit Empty Int En 
    #define mUART_RSVD0                 0x0080      // bit:    reserved 1 bit.          
    #define mUART_TWO_STOP_BITS         0x0100      // bit: two Stop Bits    
    #define mUART_PAR_EN                0x0200      // bit: prty Enable     
    #define mUART_SB_SEQ                0x0400      // bit: send Brk Sequ    
    #define mUART_LM_EN                 0x0800      // bit: loop Ack Mode En  
    #define mUART_SM_EN                 0x1000      // bit: status Mirror En 
    #define mUART_RSVD1                 0xe000      // bit:   other reserved 3 bits.
    
    
typedef union                                       // Control register
{
    mUINT_16  all;                                

    struct 
    {                                            
        mUINT_16  overRunIntEn      : 1;
        mUINT_16  prtyErrIntEn      : 1;
        mUINT_16  frameErrIntEn     : 1;
        mUINT_16  breakDetIntEn     : 1;
        mUINT_16  rcvRdyIntEn       : 1;
        mUINT_16  xmitRdyIntEn      : 1;
        mUINT_16  xmitEmptyIntEn    : 1;
        mUINT_16  rsvd0             : 1;
        
        mUINT_16  twoStopBits       : 1;
        mUINT_16  prtyEnable        : 1;
        mUINT_16  sendBrkSequ       : 1;
        mUINT_16  loopAckModeEn     : 1;
        mUINT_16  statusMirrorEn    : 1;
        mUINT_16  rsvd1             : 3;
   }bits;                          
}mtUART_CNTRL;


/*
** UART STAUTS bit masks.
*/
#define mUART_OVER_RUN_ER           0x0001
#define mUART_PARITY_ERR            0x0002
#define mUART_FRAME_ERR             0x0004
#define mUART_BREAK_DETECTED        0x0008

#define mUART_RX_RDY                0x0010
#define mUART_TX_RDY                0x0020
#define mUART_TX_EMPTY              0x0040

#define mUART_RSVD                0xff80      // Reserved 9 bits.

typedef union                                   // Status Register
{
    mUINT_16  all;                   

    struct 
    {                               
        mUINT_16  overRunEr         : 1;
        mUINT_16  parityErr         : 1;
        mUINT_16  frameErrr         : 1;
        mUINT_16  breakDetected     : 1;
        mUINT_16  xcevRdy           : 1;
        mUINT_16  xmitRdy           : 1;
        mUINT_16  xmitEmpty         : 1;
        mUINT_16  RxFifoHalfFull    : 1;
        mUINT_16  RxFifoFull        : 1;
        mUINT_16  RxToggle          : 1;
        mUINT_16  rsvd              : 6;
    }bits;  
}mtUART_STATUS;


typedef union                                   // Baud Rate Divisor
{
    mUINT_16  all;                               

    struct 
    {                                           
        mUINT_16  divisor           : 10;
        mUINT_16  uart_tbg_sel      : 1;
        mUINT_16  uart_tbg_div_sel  : 3;
        mUINT_16  uart_clk_dis      : 1;
        mUINT_16  uart_clk_sel      : 1;
    }bits;                       

}mtUART_BAUD_DIVISOR;


// UART resgiter block

typedef struct
{
    mtUART_RCV_BUFFER   xcev;           // A620
    mUINT_16            rsvd0;          // A622
    mtUART_XMIT_HOLD    xmit;           // A624
    mUINT_16            rsvd1;          // A626
    mtUART_CNTRL        cntrl;          // A628
    mUINT_16            rsvd2;          // A62A
    mtUART_STATUS       status;         // A62C
    mUINT_16            rsvd3;          // A62E
    mtUART_BAUD_DIVISOR baudRate;       // A630
}mtUART_CHIP_REGS;



//  UART configuration values

#define mUART_BAUD_9600             (9600)
#define mUART_BAUD_19200            (19200)
#define mUART_BAUD_38400            (38400)
#define mUART_BAUD_57600            (57600)
#define mUART_BAUD_115200           (115200)

   
#define mUART_INT_EN                (0x17)      // Bit pattern to enable UART INT.

/*----------------------------------------------------------------------------
 Global vars defined here.

 ---------------------------------------------------------------------------*/

#ifdef __ghs__
    #pragma ghs section bss = ".rSOC_UART"
    EXTERN volatile mtUART_CHIP_REGS     rUART;
    #pragma ghs section
#else  
    #pragma arm section zidata = "rSOC_UART"
    EXTERN volatile mtUART_CHIP_REGS     rUART;
    #pragma arm section zidata
#endif    
 
/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/
EXTERN __inline void        mUARTenTxReadyInt(void);
EXTERN __inline void        mUARTdisTxReadyInt(void);         
EXTERN __inline void        mUARTenThrEmptyInt(void);         
EXTERN __inline void        mUARTdisThrEmptyInt(void);        
EXTERN __inline void        mUARTdisUartInt(void);
EXTERN __inline void        mUARTenUartInt(void);  
EXTERN __inline void        mUARTxmitChar(mUINT_8 theChar);
EXTERN __inline void        mUARTclearErrors(mUINT_16 mask);
EXTERN __inline void        mUARTbaudRateDivisorSet(mUINT_16 divisor);         
                
EXTERN __inline mUINT_8     mUARTxcevChar(void);
EXTERN __inline mUINT_8     mUARTthrEmpty(void);
EXTERN __inline mUINT_8     mUARTthrReady(void); 

EXTERN __inline mUINT_16    mUARTreadStatus(void);

EXTERN __inline void        mUARTclockSelect(mtBOOLEAN sel);
EXTERN __inline mUINT_8     mUARTReadControl(void);
     
/*******************************************************************
*																   
*  NAME:   	    mUARTxmitChar
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  mUINT_8 bit value      											   
*																   
*  DESCRIPTION: Sets data for serial port transmit Reg.
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTxmitChar(mUINT_8 theChar)
{
    rUART.xmit.bits.data = (theChar);
}

/*******************************************************************
*																   
*  NAME:   	    mUARTxcevChar 											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Gets serial port data
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline mUINT_8 mUARTxcevChar(void)                
{
    return rUART.xcev.bits.data;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTclockSelect											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Selects clock for UART
*               - 0 : CPU clock 
*               - 1 : Oscilator clock 
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTclockSelect(mtBOOLEAN sel)                
{
    rUART.baudRate.bits.uart_clk_sel = sel; 
}        

/*******************************************************************
*																   
*  NAME:   	    mUARTtbgDivSelect											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: UART TBG Diver Select
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTtbgDivSelect(mUINT_8 sel)                
{
    rUART.baudRate.bits.uart_tbg_div_sel = sel; 
}        

/*******************************************************************
*																   
*  NAME:   	    mUARTtbgSelect											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: UART TBG Select A or B
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTtbgSelect(mtBOOLEAN sel)                
{
    rUART.baudRate.bits.uart_tbg_sel = sel; 
}

/*******************************************************************
*																   
*  NAME:   	    mUARTclkEnDis											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: UART Clock enable or disable
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTclkEnDis(mtBOOLEAN sel)                
{
    rUART.baudRate.bits.uart_clk_dis = sel; 
}

/*******************************************************************
*																   
*  NAME:   	    mUARTbaudRateDivisorSet											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  mUINT_16 divisor      											   
*																   
*  DESCRIPTION: Selects baud rate divisor
*               																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void    mUARTbaudRateDivisorSet(mUINT_16 divisor)
{
    rUART.baudRate.bits.divisor = divisor;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTreadStatus 											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Gets serial port status register.
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline mUINT_16 mUARTreadStatus(void)              
{
    return rUART.status.all;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTthrEmpty											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Checks to see if Transmit buffer and holding are both empty.
*																   
*  RETURNS:     umUINT_8 bit value set when both holding and transmit are empty.      											   
*	
********************************************************************/
__inline mUINT_8 mUARTthrEmpty(void)                
{
    return (mUINT_8)rUART.status.bits.xmitEmpty;
}
/*******************************************************************
*																   
*  NAME:   	    mUARTthrReady											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Check if transmit holding register is empty.
*																   
*  RETURNS:     mUINT_8 bit value set if serial port is ready to accept transmission      											   
*	
********************************************************************/
__inline mUINT_8 mUARTthrReady(void)                
{
    return (rUART.status.bits.xmitRdy); 
}

/*******************************************************************
*																   
*  NAME:   	    mUARTreadControl											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: return the control register content of UART.
*																   
*  RETURNS:     mUINT_8 : content of control register.
*	
********************************************************************/
__inline mUINT_8 mUARTreadControl(void)                
{
   return (rUART.cntrl.all); 
}

/*******************************************************************
*																   
*  NAME:   	    mUARTenTxReadyInt											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Enable transmit ready status to post interrupt. 
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTenTxReadyInt(void)          
{
    rUART.cntrl.bits.xmitRdyIntEn = 1;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTdisTxReadyInt 											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Disable transmit ready status to post interrupt.
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTdisTxReadyInt(void)         
{
    rUART.cntrl.bits.xmitRdyIntEn = 0;
}

/*******************************************************************
*			  													   
*  NAME:   	    mUARTenThrEmptyInt											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Enable transmit empty status to post interrupt. 
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTenThrEmptyInt(void)         
{
    rUART.cntrl.bits.xmitEmptyIntEn = 1;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTdisThrEmptyInt											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Disable transmit ready status to post interrupt.
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTdisThrEmptyInt(void)        
{
    rUART.cntrl.bits.xmitEmptyIntEn = 0;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTclearErrors											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  uint 16 mask        											   
*																   
*  DESCRIPTION: 
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTclearErrors(mUINT_16 mask)
{
    rUART.status.all = mask;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTdisUartInt											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Disable all serial port interrupt.  
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTdisUartInt(void)        
{
    rUART.cntrl.all &= ~mUART_INT_EN;
}

/*******************************************************************
*																   
*  NAME:   	    mUARTenUartInt											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Enable all serial port interrupt Rcv Rdy, Frame Err
*               Parity Err and Overrun Err.
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mUARTenUartInt(void)         
{
    rUART.cntrl.all |= mUART_INT_EN;
}


#endif // *_H_INC
