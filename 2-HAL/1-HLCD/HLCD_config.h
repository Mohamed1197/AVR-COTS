/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 21/8/2020           ********************/
/**************** SWC     :   LCD               ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

/* Macros for LCD Pins Config */
#define LCD_u8_CONTROL_PORT         DIO_u8_PORTB
#define LCD_u8_RS_PIN               DIO_u8_PIN0
#define LCD_u8_RW_PIN               DIO_u8_PIN1
#define LCD_u8_E_PIN                DIO_u8_PIN2

#define LCD_u8_DATA_PORT            DIO_u8_PORTB

#define LCD_u8_4BIT_START_PIN       DIO_u8_PIN4
#define LCD_u8_4BIT_END_PIN         DIO_u8_PIN7

#define LCD_MODE                    LCD_4_BIT_MODE


#endif
