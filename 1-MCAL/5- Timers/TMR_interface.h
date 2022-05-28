/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 25/9/2020           ********************/
/**************** SWC     :     TMR             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

void TMR_voidTimer0Init(void);

u8   TMR_u8Timer0OVFSetCallBack(void(*Copy_pf)(void));

u8   TMR_u8Timer0CTCSetCallBack(void(*Copy_pf)(void));

void TMR_voidTimer0SetCompareMatchValue(u8 Copy_u8OCRValue);

void TMR_voidTimer1Init(void);

void TMR_voidTimer1SetCompareMatchValueChannelA(u16 Copy_u16CompareMatchValue);

u8   TMR_u8Timer1GetCounterValue(u16 * Copy_pu16CounterValue);

u8   TMR_u8Timer1CTCSetCallBack(void (*Copy_pf)(void));

void TMR_voidTimer1CTCCounter(u16 Copy_u16CTCCounter);

void TMR_voidHWICUEnable(void);

void TMR_voidHWICUDisable(void);

u8   TMR_u8GetPWMTotalPeriod(u32 * Copy_pu32TotalPeriod);

u8   TMR_u8GetPWMDutyCycle(u8 * Copy_pu8DutyCycle);

u8   TMR_u8GetPWMOnPeriod(u16 * Copy_pu16OnPeriod);

#endif
