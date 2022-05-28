/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 18/9/2020           ********************/
/**************** SWC     :     ADC             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef ACD_INTERFACE_H
#define ACD_INTERFACE_H

#define ADC_u8_CHANNEL_0                      0
#define ADC_u8_CHANNEL_1                      1
#define ADC_u8_CHANNEL_2                      2
#define ADC_u8_CHANNEL_3                      3
#define ADC_u8_CHANNEL_4                      4
#define ADC_u8_CHANNEL_5                      5
#define ADC_u8_CHANNEL_6                      6
#define ADC_u8_CHANNEL_7                      7
#define ADC_u8_CHANNEL_0_CH0_G10              8
#define ADC_u8_CHANNEL_1_CH0_G10              9
#define ADC_u8_CHANNEL_0_CH0_G200             10
#define ADC_u8_CHANNEL_1_CH0_G200             11
#define ADC_u8_CHANNEL_2_CH2_G10              12
#define ADC_u8_CHANNEL_3_CH2_G10              13
#define ADC_u8_CHANNEL_2_CH2_G200             14
#define ADC_u8_CHANNEL_3_CH2_G200             15
#define ADC_u8_CHANNEL_0_CH1_G1               16
#define ADC_u8_CHANNEL_1_CH1_G1               17
#define ADC_u8_CHANNEL_2_CH1_G1               18
#define ADC_u8_CHANNEL_3_CH1_G1               19
#define ADC_u8_CHANNEL_4_CH1_G1               20
#define ADC_u8_CHANNEL_5_CH1_G1               21
#define ADC_u8_CHANNEL_6_CH1_G1               22
#define ADC_u8_CHANNEL_7_CH1_G1               23
#define ADC_u8_CHANNEL_0_CH2_G1               24
#define ADC_u8_CHANNEL_1_CH2_G1               25
#define ADC_u8_CHANNEL_2_CH2_G1               26
#define ADC_u8_CHANNEL_3_CH2_G1               27
#define ADC_u8_CHANNEL_4_CH2_G1               28
#define ADC_u8_CHANNEL_5_CH2_G1               29


void ADC_voidInit(void);

u8 ADC_u8GetDigitalValueSunchNonBlocking(u8 Copy_u8ChannelNb,u16* Copy_pu16DigitalValue);

u8 ADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNb,void(*Copy_PfNotification)(u16));

u8 ADC_u8ReadADCRegister(u16 * Copy_pu16ADCRegValue);

#endif
