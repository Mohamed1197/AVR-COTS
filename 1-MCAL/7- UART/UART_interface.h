/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 09/10/2020          ********************/
/**************** SWC     :     UART            ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void UART_voidInit(void);

void UART_voidSendDataByte(u8 Copy_u8DataByte);

u8   UART_u8RecieveDataByte( void);

void UART_voidSendDataStringSynch(u8 *Copy_puSendDataString);

u8*  UART_u8RecieveDataStringSynch(void);

u8   UART_voidSendDataStringASynch( u8 * Copy_pu8SendDataByte , void (*Copy_pfSendDataString)(void));

u8   UART_u8RecieveDataStringASynch( u8 * Copy_puReceiveDataString , u8 Copy_u8Size , void (*Copy_pfReceiveDataString)(void));

#endif
