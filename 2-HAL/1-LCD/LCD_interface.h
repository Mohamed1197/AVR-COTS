/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 21/8/2020           ********************/
/**************** SWC     :   LCD               ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_u8_LINE0           0
#define LCD_u8_LINE1           1

void LCD_voidInit        (void);

void LCD_voidClear       (void);

void LCD_voidCursorBlinkerOff(void);
					     
void LCD_voidSendCmnd    (u8 Copy_u8Cmnd);
					     
void LCD_voidSendChar    (u8 Copy_u8Char);
						
void LCD_voidWriteString (u8 *Copy_pu8String);

u8 LCD_u8_GoTo_XY        (u8 Copy_u8X,u8 Copy_u8Y);

void LCD_voidWriteNumber (u32 Copy_u32Num);


void LCD_voidSendSpecialChar(u8 Copy_u8CharNo,u8 Copy_u8X,u8 Copy_u8Y,u8 * Copy_PSpecialChar);

void LCD_voidShiftDispRight(void);

void LCD_voidShiftDispLeft(void);



#endif                  
