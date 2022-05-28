/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 17/10/2020          ********************/
/**************** SWC     :    EEPROM           ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#include "TWI_interface.h"

#include "EEPROM_config.h"
#include "EEPROM_private.h"
#include "EERPROM_interface.h"


void EEPROM_voidInit(void)
{
	TWI_voidMasterInit();
}

u8   EEPROM_u8WriteDataByte(u8 Copy_u8Data,u16 Copy_u16ByteAddress)
{
	u8             Local_u8ErrorState     = STD_TYPES_OK;
	TWI_ErrorState Local_enuTWIErrorState = TWI_OK;
	/* Start Condition */
	Local_enuTWIErrorState = TWI_enuSendStartCondition();
	Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

	/* Send Slave Address with Write Bit */
	Local_enuTWIErrorState = TWI_enuSendSlaveWithWrite((EEPROM_u8_FIXED_ADDRESS)|(EEPROM_u8_A2_VALUE<<2)|((u8)(Copy_u16ByteAddress>>8)));
	Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

	/* Send The Rest Of The Byte Address */
	Local_enuTWIErrorState = TWI_enuSendDataByte((u8)Copy_u16ByteAddress);
	Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

	/* Send The Data Byte */
	Local_enuTWIErrorState = TWI_enuSendDataByte((u8)Copy_u8Data);
	Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

	/* Send Stop Condition */
	TWI_voidSendStopCondition();
	_delay_ms(5);
	return Local_u8ErrorState;
}

u8   EEPROM_u8ReadDataByte(u8 * Copy_pu8ReceivedData ,u16 Copy_u16ByteAddress )
{
	u8             Local_u8ErrorState     = STD_TYPES_OK;
	TWI_ErrorState Local_enuTWIErrorState = TWI_OK;
	if(Copy_pu8ReceivedData != NULL)
	{
		u8 Local_u8EEPROMAddress = (EEPROM_u8_FIXED_ADDRESS)|(EEPROM_u8_A2_VALUE<<2)|((u8)(Copy_u16ByteAddress>>8));
		/* Send Start Condition */
		Local_enuTWIErrorState = TWI_enuSendStartCondition();
		Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

		/* Send Slave Address with Write Bit */
		Local_enuTWIErrorState = TWI_enuSendSlaveWithWrite(Local_u8EEPROMAddress);
		Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

		/* Send The Rest Of The Byte Address */
		Local_enuTWIErrorState = TWI_enuSendDataByte((u8)Copy_u16ByteAddress);
		Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

		/* Send Repeated Start Condition */
		Local_enuTWIErrorState = TWI_enuSendRepeatedStartCondition();
		Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

		/* Send Slave Address with Read Bit */
		Local_enuTWIErrorState = TWI_enuSendSlaveWithRead(Local_u8EEPROMAddress);
		Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

		/* Read Data */
		Local_enuTWIErrorState = TWI_enuReceiveDataByte(Copy_pu8ReceivedData);
		Local_u8ErrorState     = Private_u8ErrorStateCheck(Local_enuTWIErrorState);

		/* Send Stop Condition */
		TWI_voidSendStopCondition();

		_delay_ms(5);


	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;

}

static u8   Private_u8ErrorStateCheck(TWI_ErrorState Copy_enuErrorState)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_enuErrorState != TWI_OK)
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
