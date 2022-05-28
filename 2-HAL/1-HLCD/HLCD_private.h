/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 21/8/2020           ********************/
/**************** SWC     :   LCD               ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H



 void HLCD_voidSendChar (u8 Copy_u8Char);



#define LCD_4_BIT_MODE     0
#define LCD_8_BIT_MODE     1

#define FUNCTION_SET_4BITS      0b00101000
#define FUNCTION_SET_8BITS      0b00111000
#define LCD_DISPLAY_ON_OFF      0b00001100
#define LCD_DISPLAY_CLEAR       0b00000001
#define LCD_ENTRY_MODE          0b00000110

#define LCD_BLINKER_OFF         0b00001100
#define LCD_SHIFT_RIGHT         0b00011100
#define LCD_SHIFT_LEFT          0b00011000






#endif
