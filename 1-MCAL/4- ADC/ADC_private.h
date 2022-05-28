/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 18/9/2020           ********************/
/**************** SWC     :     ADC             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef ACD_PRIVATE_H
#define ACD_PRIVATE_H

#define ADC_u8_ADMUX_REG           *((volatile u8*)0x27)
#define ADC_u8_ADCSRA_REG          *((volatile u8*)0x26)
#define ADC_u8_ADCH_REG            *((volatile u8*)0x25)
#define ADC_u8_ADCL_REG            *((volatile u8*)0x24)

#define ADC_u16_ADC_REG            *((volatile u16*)0x24)

#define ADC_u8_SFIOR_REG           *((volatile u8*)0x50)

#endif
