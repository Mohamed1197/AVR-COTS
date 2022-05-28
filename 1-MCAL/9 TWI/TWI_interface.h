/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 16/10/2020          ********************/
/**************** SWC     :     TWI             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum
{
	TWI_OK = 1,
	TWI_SC_ERROR,
	TWI_RSC_ERROR,
	TWI_SLA_W_ERROR,
	TWI_SLA_R_ERROR,
	TWI_DATA_W_ERROR,
	TWI_NULL_POINTER,
	TWI_DATA_R_ERROR
}TWI_ErrorState;


void TWI_voidMasterInit(void);

u8   TWI_u8SlaveInit(u8 Copy_u8SlaveAddress);

TWI_ErrorState   TWI_enuSendStartCondition(void);

TWI_ErrorState   TWI_enuSendRepeatedStartCondition(void);

TWI_ErrorState   TWI_enuSendSlaveWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrorState   TWI_enuSendSlaveWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrorState   TWI_enuSendDataByte(u8 Copy_u8Data);

TWI_ErrorState   TWI_enuReceiveDataByte(u8 * Copy_pu8ReceivedData);

void TWI_voidSendStopCondition(void);

#endif
