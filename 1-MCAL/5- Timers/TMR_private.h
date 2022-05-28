/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 25/9/2020           ********************/
/**************** SWC     :     TMR             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef TMR_PRIVATE_H
#define TMR_PRIVATE_H

#define TMR_u8_OCR0_REG               *((volatile u8*)0x5C)
#define TMR_u8_TIMSK_REG              *((volatile u8*)0x59)
#define TMR_u8_TIFR_REG               *((volatile u8*)0x58)
#define TMR_u8_TCCR0_REG              *((volatile u8*)0x53)
#define TMR_u8_TCNT0_REG              *((volatile u8*)0x52)


#define TMR_u8_TCCR1A_REG             *((volatile u8*)0x4F)
#define TMR_u8_TCCR1B_REG             *((volatile u8*)0x4E)

#define TMR_u8_TCNT1H_REG             *((volatile u8*)0x4D)
#define TMR_u8_TCNT1L_REG             *((volatile u8*)0x4C)

#define TMR_u16_TCNT1_REG             *((volatile u16*)0x4C)

#define TMR_u8_OCR1AH_REG             *((volatile u8*)0x4B)
#define TMR_u8_OCR1AL_REG             *((volatile u8*)0x4A)

#define TMR_u16_OCR1A_REG             *((volatile u16*)0x4A)

#define TMR_u8_OCR1BH_REG             *((volatile u8*)0x49)
#define TMR_u8_OCR1BL_REG             *((volatile u8*)0x48)

#define TMR_u16_OCR1B_REG             *((volatile u16*)0x48)

#define TMR_u8_ICR1H_REG             *((volatile u8*)0x47)
#define TMR_u8_ICR1L_REG             *((volatile u8*)0x46)

#define TMR_u16_ICR1_REG             *((volatile u16*)0x46)

#endif
