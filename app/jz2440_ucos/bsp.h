/*File Name:bsp.h
**By ma-zhihui
**@2011-7-20
**Description: myInitLED用于初始化LED灯，myInitTimer4用于初始化定时器4，
**定时器4用作ucos ii 的时钟节拍，为100 HZ
*/
#ifndef _BSP_H
#define _BSP_H

void myInitLED(void);
void myInitTimer4(void);
void myInitUart0(void);
void myInitHtmr0(void);
#endif