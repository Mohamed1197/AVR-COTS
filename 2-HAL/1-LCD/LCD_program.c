/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 21/8/2020           ********************/
/**************** SWC     :   LCD               ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void LCD_voidInit     (void)
{
	_delay_ms(35);
	/* Function Set Cmnd 0b00111000 */
	LCD_voidSendCmnd(0b00111000);
	_delay_us(40);
	LCD_voidSendCmnd(0b00001111);
	_delay_us(40);
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
	LCD_voidSendCmnd(0b00000110);
	
}

void LCD_voidClear       (void)
{
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(20);
}

void LCD_voidCursorBlinkerOff(void)
{
	LCD_voidSendCmnd(0b00001100);
	_delay_ms(20);
}

void LCD_voidSendCmnd (u8 Copy_u8Cmnd)
{
	/* Rs = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/* Rw = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	/* Send Cmnd byte to the Data Pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
	/* Pulse of Enable E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	_delay_us(1);
}
void LCD_voidSendChar (u8 Copy_u8Char)
{
	/* Rs = 1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	/* Rw = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	/* Send Char byte to the Data Pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
	/* Pulse of Enable E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	_delay_us(1);
}
void LCD_voidWriteString (u8 * Copy_pu8String)
{
	if(Copy_pu8String != NULL )
	{
	    u8 x = 0;
	    u8 i = 0;
		while(Copy_pu8String[x] != '\0')
		{
		 x++ ;
		 for(  ; i < x; i++)
		 {
		  /* Write Character on LCD */
		  LCD_voidSendChar (Copy_pu8String[i]);
		 }
		 
		}
	}
	
}
u8 LCD_u8_GoTo_XY     (u8 Copy_u8X,u8 Copy_u8Y)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	if((Copy_u8X <=1)&&(Copy_u8Y <= 39))
	{
		switch(Copy_u8X)
		{
		case LCD_u8_LINE0 : LCD_voidSendCmnd(0x80 + Copy_u8Y);break;

		case LCD_u8_LINE1 : LCD_voidSendCmnd(0xC0 + Copy_u8Y);break;
		}
	}
	else
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}


}
void LCD_voidWriteNumber (u32  Copy_u32Num)
{

	u8 Arr[10];
	u8 Local_Remainder = 1;
	u32 Local_Number = Copy_u32Num;
	u8 Local_Counter = 0;
	u8 Local_Counter2 ;


	for(u8 initial = 10 ; initial >=1 ; initial--)
	{
		Local_Remainder = Local_Number % 10 ;
		Local_Number    = Local_Number /10 ;

		if((Local_Remainder ==0) && (Local_Number<1) && (Local_Counter>0) )
		{
			break;
		}
		Local_Counter ++;
		Arr[initial-1] = Local_Remainder ;
	}

	for(Local_Counter2 = 10 - Local_Counter; Local_Counter2 < 10 ; Local_Counter2 ++)
	{
		LCD_voidSendChar(Arr[Local_Counter2]+48);
	}



}

void LCD_voidSendSpecialChar(u8 Copy_u8CharNo,u8 Copy_u8X,u8 Copy_u8Y,u8 * Copy_PSpecialChar)
{

	switch(Copy_u8CharNo)
	{
	case 0:
		LCD_voidSendCmnd(0b01000000);

		break;
	case 1:
	    LCD_voidSendCmnd(0b01001000);
		break;
	case 2:
	    LCD_voidSendCmnd(0b01010000);
		break;
	case 3:
	    LCD_voidSendCmnd(0b01011000);
		break;
	case 4:
	    LCD_voidSendCmnd(0b01100000);
		break;
	case 5:
	    LCD_voidSendCmnd(0b01101000);
		break;
	case 6:
	    LCD_voidSendCmnd(0b01110000);
		break;
	case 7:
	    LCD_voidSendCmnd(0b01111000);
		break;
	}


	 for(u8 specialchar=0 ; specialchar<8 ; specialchar++ )
	 {
		 LCD_voidSendChar(Copy_PSpecialChar[specialchar]);
	 }

	 LCD_u8_GoTo_XY( Copy_u8X, Copy_u8Y);
	 LCD_voidSendChar(Copy_u8CharNo);


}

void LCD_voidShiftDispRight(void)
{
	LCD_voidSendCmnd(0b00011100);
}
void LCD_voidShiftDispLeft(void)
{
	LCD_voidSendCmnd(0b00011000);
}

