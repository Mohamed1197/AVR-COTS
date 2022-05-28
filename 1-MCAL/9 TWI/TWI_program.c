/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 16/10/2020          ********************/
/**************** SWC     :     TWI             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void TWI_voidMasterInit(void)
{
	/* Set Prescaler Value */
	CLR_BIT(TWI_u8_TWSR_REG,1);
	CLR_BIT(TWI_u8_TWSR_REG,0);
	
	/* Set TWBR Value 200KHZ */
	TWI_u8_TWBR_REG = 12;
	
	/* Enable ACKnowledgemnet */
	SET_BIT(TWI_u8_TWCR_REG,6);
	
	/* Enable TWI */
	SET_BIT(TWI_u8_TWCR_REG,2);
}

u8   TWI_u8SlaveInit(u8 Copy_u8SlaveAddress)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	/* Set Slave Adress IN TWAR REG */
	TWI_u8_TWAR_REG = Copy_u8SlaveAddress << 1;
	
    /* Enable ACKnowledgemnet */
	SET_BIT(TWI_u8_TWCR_REG,6);
	
	/* Enable TWI */
	SET_BIT(TWI_u8_TWCR_REG,2);
}

TWI_ErrorState   TWI_enuSendStartCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	
	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
	
	/* Wait for the Flag */
	while(!(GET_BIT(TWI_u8_TWCR_REG,7)));
	
	/* Check ACKnowledgemnt => START CONDITION */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x08 )
	{
		Local_enuErrorState = TWI_SC_ERROR;
	}
	return Local_enuErrorState;
}

TWI_ErrorState   TWI_enuSendRepeatedStartCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	
	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
	
	/* Wait for the Flag */
	while(!(GET_BIT(TWI_u8_TWCR_REG,7)));
	
	/* Check ACKnowledgemnt => START CONDITION */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x10 )
	{
		Local_enuErrorState = TWI_RSC_ERROR;
	}
	return Local_enuErrorState;
}

TWI_ErrorState   TWI_enuSendSlaveWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK;
	/* Set TWDR = SL Address + Write*/
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress << 1;
	CLR_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	
	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
	
	/* Wait for the Flag */
	while(!(GET_BIT(TWI_u8_TWCR_REG,7)));
	
	/* Check ACKnowledgemnt => Slave Address + W */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x18 )
	{
		Local_enuErrorState = TWI_SLA_W_ERROR;
	}
	return Local_enuErrorState;
}

TWI_ErrorState   TWI_enuSendSlaveWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK;
	/* Set TWDR = SL Address + Write*/
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress << 1;
	SET_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	
	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
	
	/* Wait for the Flag */
	while(!(GET_BIT(TWI_u8_TWCR_REG,7)));
	
	/* Check ACKnowledgemnt => Slave Address + W */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x40 )
	{
		Local_enuErrorState = TWI_SLA_R_ERROR;
	}
	return Local_enuErrorState;
}

TWI_ErrorState   TWI_enuSendDataByte(u8 Copy_u8Data)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK;
	/* Set TWDR = Data + Read*/
	TWI_u8_TWDR_REG = Copy_u8Data;

	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
	
	/* Wait for the Flag */
	while(!(GET_BIT(TWI_u8_TWCR_REG,7)));
	
	/* Check ACKnowledgemnt => Slave Address + W */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x28 )
	{
		Local_enuErrorState = TWI_DATA_W_ERROR;
	}
	return Local_enuErrorState;
}

TWI_ErrorState   TWI_enuReceiveDataByte(u8 * Copy_pu8ReceivedData)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK;

	/* Check pointer */
	if(Copy_pu8ReceivedData != NULL)
	{

		/* Clear Flag */
		SET_BIT(TWI_u8_TWCR_REG,7);

		/* Wait for the Flag */
		while(!(GET_BIT(TWI_u8_TWCR_REG,7)));

		/* Check ACKnowledgemnt => Slave Address + W */
		if((TWI_u8_TWSR_REG & 0xF8) != 0x50 )
		{
			Local_enuErrorState = TWI_DATA_R_ERROR;
		}
		else
		{
			/* Read Data */
			*Copy_pu8ReceivedData = TWI_u8_TWDR_REG;
		}
	}
	else
	{
		Local_enuErrorState = TWI_NULL_POINTER;
	}
	
	return Local_enuErrorState;
}

void TWI_voidSendStopCondition(void)
{
	/* Send Stop Condition */
	SET_BIT(TWI_u8_TWCR_REG,4);
	
	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
}
