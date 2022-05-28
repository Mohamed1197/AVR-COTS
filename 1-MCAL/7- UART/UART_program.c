/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 09/10/2020          ********************/
/**************** SWC     :     UART            ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"

static u8 * Global_pu8SendByte = NULL;
static u8 * Global_pu8ReceiveByte = NULL;

static void (*UART_pfSendString)(void) = NULL;
static void (*UART_pfRecieveString)(void) = NULL;

static u8 UART_u8BusyFlag = 0 ;

static u8 Global_u8Size = 0;

static u8 Global_u8Counter = 0;

void UART_voidInit(void)
{
	u8 Local_u8UCSRCValue = 0x80;
	/* Select Baud Rate = 9600 */
	u16 Local_u16UBRRValue = UBRR_VALUE;
	
	UART_u8_UBRRL_REG = (u8)Local_u16UBRRValue;
	UART_u8_UBRRH_REG =(u8)(Local_u16UBRRValue>>8);
	
//	/* Enable Rx,Tx */
//	SET_BIT(UART_u8_UCSRB_REG,4);
//	SET_BIT(UART_u8_UCSRB_REG,3);
//
//	/* Character Size = 8 Bits */
//	CLR_BIT(UART_u8_UCSRB_REG,2);
//	SET_BIT(Local_u8UCSRCValue,2);
//	SET_BIT(Local_u8UCSRCValue,1);
//
//	/* ASynch Mode */
//	CLR_BIT(Local_u8UCSRCValue,6);
//
//	/* Disable Parity Bit */
//	CLR_BIT(Local_u8UCSRCValue,5);
//	CLR_BIT(Local_u8UCSRCValue,4);
//
//	/* StopBits  = 2 */
//	SET_BIT(Local_u8UCSRCValue,3);


	/* UART TX Enable \ Disable  */
#if(TX_MODE == TX_ENABLE)
	{
		SET_BIT(UART_u8_UCSRB_REG,3);
	}
#elif(TX_MODE == TX_DISABLE)
	{
		CLR_BIT(UART_u8_UCSRB_REG,3);
	}
#endif

	/* UART RX Enable \ Disable  */
#if(RX_MODE == RX_ENABLE)
	{
		SET_BIT(UART_u8_UCSRB_REG,4);
	}
#elif(RX_MODE == RX_DISABLE)
	{
		CLR_BIT(UART_u8_UCSRB_REG,4);
	}
#endif

	/* Character Size */
#if(CHARACTER_SIZE == CHARCTER_5_BIT)
	{
		CLR_BIT(UART_u8_UCSRB_REG,2);
		CLR_BIT(Local_u8UCSRCValue,2);
		CLR_BIT(Local_u8UCSRCValue,1);
	}
#elif(CHARACTER_SIZE == CHARCTER_6_BIT)
	{
		CLR_BIT(UART_u8_UCSRB_REG,2);
		CLR_BIT(Local_u8UCSRCValue,2);
		SET_BIT(Local_u8UCSRCValue,1);
	}
#elif(CHARACTER_SIZE == CHARCTER_7_BIT)
	{
		CLR_BIT(UART_u8_UCSRB_REG,2);
		SET_BIT(Local_u8UCSRCValue,2);
		CLR_BIT(Local_u8UCSRCValue,1);
	}
#elif(CHARACTER_SIZE == CHARCTER_8_BIT)
	{
		CLR_BIT(UART_u8_UCSRB_REG,2);
		SET_BIT(Local_u8UCSRCValue,2);
		SET_BIT(Local_u8UCSRCValue,1);
	}
#elif(CHARACTER_SIZE == CHARCTER_9_BIT)
	{
		SET_BIT(UART_u8_UCSRB_REG,2);
		SET_BIT(Local_u8UCSRCValue,2);
		SET_BIT(Local_u8UCSRCValue,1);
	}
#endif

	/* Select UART Operation Mode */
#if(OPERATION_MODE == SYNC_OPERATION)
	{
		SET_BIT(Local_u8UCSRCValue,6);
	}
#elif(OPERATION_MODE == ASYNC_OPERATION)
	{
		CLR_BIT(Local_u8UCSRCValue,6);
	}
#endif

	/* Parity Bit Mode */
#if(PARITY_MODE == DISABLED)
	{
		CLR_BIT(Local_u8UCSRCValue,5);
		CLR_BIT(Local_u8UCSRCValue,4);
	}
#elif(PARITY_MODE == EVEN_PARITY)
	{
		SET_BIT(Local_u8UCSRCValue,5);
		CLR_BIT(Local_u8UCSRCValue,4);
	}
#elif(PARITY_MODE == ODD_PARITY)
	{
		SET_BIT(Local_u8UCSRCValue,5);
		SET_BIT(Local_u8UCSRCValue,4);
	}
#endif

	/* Stop Bits */
#if(STOP_BITS == STOP_1_BIT)
	{
		CLR_BIT(Local_u8UCSRCValue,3);
	}
#elif(STOP_BITS == STOP_2_BIT)
	{
		SET_BIT(Local_u8UCSRCValue,3);
	}
#endif

	/* Update the UCSRC REG */
	UART_u8_UCSRC_REG = Local_u8UCSRCValue;
}

void UART_voidSendDataByte(u8 Copy_u8DataByte)
{
	/* Check if Tx Buffer is Empty */
	while((GET_BIT(UART_u8_UCSRA_REG,5)) == 0);
	//while(!GET_BIT(UART_u8_UCSRA_REG,5));
	UART_u8_UDR_REG = Copy_u8DataByte;
}

u8   UART_u8RecieveDataByte( void)
{

		/* Check the Reciece flag */
		while( (GET_BIT(UART_u8_UCSRA_REG,7)) == 0 );
		/* Read Data */
		return UART_u8_UDR_REG;

}
void UART_voidSendDataStringSynch(u8  *Copy_puSendDataString)
{
	if(Copy_puSendDataString != NULL )
	{

		while(*Copy_puSendDataString != 0x00)
		{

		  /* Write String  */
			 UART_voidSendDataByte (*Copy_puSendDataString);
			 Copy_puSendDataString++;
		 }

	}

}
u8*  UART_u8RecieveDataStringSynch(void)
{

	u8 i;
	static u8  arr[30] ;

	for(i=0 ; i<29 ; i++ )
	{
		if(arr[i-1] == ' ')
		{
			for( ; i < 29 ; i++)
			{
			  arr[i] = NULL;
			}
		}
		else
		{
			arr[i] = UART_u8RecieveDataByte();

		}
	}
	arr[29] = NULL;
	return arr;
}

u8   UART_voidSendDataStringASynch( u8 * Copy_pu8SendDataByte , void (*Copy_pfSendDataString)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if((Copy_pfSendDataString != NULL) && (Copy_pu8SendDataByte != NULL) && (UART_u8BusyFlag == 0))
	{
		/* UART is Busy */
		UART_u8BusyFlag = 1;
		/* Updating Global Pointers with the input parameters */
		Copy_pu8SendDataByte = Global_pu8SendByte;
		 UART_pfSendString = Copy_pfSendDataString;
		/* Enable Interrupt of UDR is Empty PIE */
		SET_BIT(UART_u8_UCSRB_REG,5);

		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;

}

u8   UART_u8RecieveDataStringASynch( u8 * Copy_puReceiveDataString , u8 Copy_u8Size , void (*Copy_pfReceiveDataString)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if((Copy_pfReceiveDataString != NULL) && (Copy_puReceiveDataString != NULL) && (UART_u8BusyFlag == 0))
	{
		/* UART is Busy */
		UART_u8BusyFlag = 1;
		/* Updating Global Pointers with the input parameters */
		Copy_puReceiveDataString = Global_pu8ReceiveByte;
		UART_pfRecieveString = Copy_pfReceiveDataString ;
		/* Update Global size with the input parameter */
		Copy_u8Size = Global_u8Size;
		if((GET_BIT(UART_u8_UCSRA_REG,7)) == 1)
		{
			Global_pu8ReceiveByte[Global_u8Counter] = UART_u8_UDR_REG ;
			Global_u8Counter ++ ;
		}
		/* Enable Rx Interrupt PIE */
		SET_BIT(UART_u8_UCSRB_REG,7);

		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;

}
/* Prototype of USART RX ISR */
void __vector_13(void)   __attribute__((signal));
void __vector_13(void)
{
	if(Global_u8Counter != Global_u8Size)
	{
		Global_pu8ReceiveByte[Global_u8Counter] = UART_u8_UDR_REG;
		Global_u8Counter ++ ;
	}
	else
	{
		/* Disable Rx Interrupt PIE */
		CLR_BIT(UART_u8_UCSRB_REG,7);
		/* Clear busy Flag */
		UART_u8BusyFlag = 0 ;
		/* Clear Counter */
		Global_u8Counter = 0;
		/* Call Notification Function */
		UART_pfRecieveString();

	}

}
/* Prototype of USART Tx Reg Empty (UDRE) ISR */
void __vector_14(void)   __attribute__((signal));
void __vector_14(void)
{
	static u8 Local_u8Counter = 0;
	if(Global_pu8SendByte[Local_u8Counter] != '\0')
	{
		UART_u8_UDR_REG = Global_pu8SendByte[Local_u8Counter];
		Local_u8Counter ++ ;
	}
	else
	{
		/* Disable Interrupt of UDR is Empty PIE */
		CLR_BIT(UART_u8_UCSRB_REG,5);
		/* Clear busy Flag */
		UART_u8BusyFlag = 0 ;
		/* Clear Counter */
		Local_u8Counter = 0;
		/* Call Notification Function */
		UART_pfSendString();

	}

}
