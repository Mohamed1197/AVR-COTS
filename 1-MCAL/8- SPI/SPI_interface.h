/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 10/10/2020          ********************/
/**************** SWC     :     SPI             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_voidInit(void);

u8   SPI_u8TransRecive(u8 Copy_u8DataByte ,u8 * Copy_pu8RecievedData);

#endif