/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 17/10/2020          ********************/
/**************** SWC     :    EEPROM           ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

void EEPROM_voidInit(void);

u8   EEPROM_u8WriteDataByte(u8 Copy_u8Data,u16 Copy_u16ByteAddress);

u8   EEPROM_u8ReadDataByte(u8 * Copy_pu8ReceivedData ,u16 Copy_u16ByteAddress );

#endif