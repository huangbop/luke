/*
 * Copyright (C) 2014 Huang Bo
 */

#include "stdint.h"


#define _MMUTT_STARTADDRESS	 0x31000000

#define DESC_SEC		(0x2|(1<<4))
#define CB				(3<<2)  //cache_on, write_back
#define CNB				(2<<2)  //cache_on, write_through
#define NCB				(1<<2)  //cache_off,WR_BUF on
#define NCNB				(0<<2)  //cache_off,WR_BUF off
#define AP_RW			(3<<10) //supervisor=RW, user=RW
#define AP_RO			(2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT	(0x0)
#define DOMAIN_CHK		(0x1)
#define DOMAIN_NOTCHK	(0x3)
#define DOMAIN0			(0x0<<5)
#define DOMAIN1			(0x1<<5)

#define DOMAIN0_ATTR	(DOMAIN_CHK<<0)
#define DOMAIN1_ATTR	(DOMAIN_FAULT<<2)

#define RW_CB		(AP_RW|DOMAIN0|CB|DESC_SEC)
#define RW_CNB		(AP_RW|DOMAIN0|CNB|DESC_SEC)
#define RW_NCNB		(AP_RW|DOMAIN0|NCNB|DESC_SEC)
#define RW_FAULT	(AP_RW|DOMAIN1|NCNB|DESC_SEC)

#ifdef __CC_ARM
void mmu_setttbase(uint32_t i)
{
    __asm
    {
        mcr p15, 0, i, c2, c0, 0
    }
}

void mmu_set_domain(uint32_t i)
{
    __asm
    {
        mcr p15,0, i, c3, c0,  0
    }
}

void mmu_enable()
{
    /* register */ uint32_t value;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;

	int h = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	int n = 0;

	int o = 0;
	int p = 0;
	int q = 0;
	
	a++;
	b++;
	c++;
	d++;
	e++;
	f++;
	g++;

	h++;
	i++;
	j++;
	k++;
	l++;
	m++;
	n++;

	o++;
	p++;
	q++;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x01
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x01
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_icache()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x1000
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_dcache()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x04
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_icache()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x1000
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_dcache()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x04
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_alignfault()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x02
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_alignfault()
{
    register uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x02
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_clean_invalidated_cache_index(int index)
{
    __asm
    {
        mcr p15, 0, index, c7, c14, 2
    }
}

void mmu_invalidate_tlb()
{
    register uint32_t value;

    value = 0;
    __asm
    {
        mcr p15, 0, value, c8, c7, 0
    }
}

void mmu_invalidate_icache()
{
    register uint32_t value;

    value = 0;

    __asm
    {
        mcr p15, 0, value, c7, c5, 0
    }
}
#endif

void mmu_setmtt(int vaddrStart,int vaddrEnd,int paddrStart,int attr)
{
    volatile uint32_t *pTT;
    volatile int i,nSec;
    pTT=(uint32_t *)_MMUTT_STARTADDRESS+(vaddrStart>>20);
    nSec=(vaddrEnd>>20)-(vaddrStart>>20);
    for(i=0;i<=nSec;i++)
    {
		*pTT = attr |(((paddrStart>>20)+i)<<20);
		pTT++;
    }
}

void mmu_init(void)
{
	//========================== IMPORTANT NOTE =========================
	//The current stack and code area can't be re-mapped in this routine.
	//If you want memory map mapped freely, your own sophiscated mmu
	//initialization code is needed.
	//===================================================================


	mmu_setmtt(0x30000000,0x30100000,0x30000000, RW_CB); /* self */
		
	mmu_setmtt(0x56000000,0x56100000,(int)0x56000000, RW_CB); /* GPF */
	mmu_setmtt(0x51000000,0x51100000,(int)0x51000000, RW_CB); /* timer */
	mmu_setmtt(0x4a000000,0x4a100000,(int)0x4a000000, RW_CB); /* interrupt */
	mmu_setmtt(0x50000000,0x50100000,(int)0x50000000, RW_CB); /* uart */

	mmu_setmtt(0x00000000,0x00100000,(int)0x30000000, RW_CB); /* int vectors */


	/* mmu_setmtt(0x00000000,0x00100000,0x30000000,RW_CB);  */

	/* mmu_setmtt(0x56000000,0x56100000,0x56000000, RW_CB); /\* regs *\/ */
	
	
	mmu_setttbase(_MMUTT_STARTADDRESS);

	/* DOMAIN1: no_access, DOMAIN0,2~15=client(AP is checked) */
	/* mmu_set_domain(0x55555550|DOMAIN1_ATTR|DOMAIN0_ATTR); */
	mmu_set_domain(3);

	/* mmu_enable_alignfault(); */

	mmu_enable();

}

