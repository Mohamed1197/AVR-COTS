/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :      23/05/2022          ********************/
/**************** SWC     :         DIO              ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/
/* Lib Layer*/
#include "../../LIB/LBIT_MATH.h"
#include "../../LIB/LSTD_TYPES.h"
#include "MDIO_config.h"
#include "MDIO_interface.h"
#include "MDIO_private.h"

u8 MDIO_u8Init            (void)
{
     DDRA_u8_REG = CONC(DIO_u8_PA7_INITIAL_DIRECTION,DIO_u8_PA6_INITIAL_DIRECTION,DIO_u8_PA5_INITIAL_DIRECTION,DIO_u8_PA4_INITIAL_DIRECTION,
	                    DIO_u8_PA3_INITIAL_DIRECTION,DIO_u8_PA2_INITIAL_DIRECTION,DIO_u8_PA1_INITIAL_DIRECTION,DIO_u8_PA0_INITIAL_DIRECTION); 
     
	 DDRB_u8_REG = CONC(DIO_u8_PB7_INITIAL_DIRECTION,DIO_u8_PB6_INITIAL_DIRECTION,DIO_u8_PB5_INITIAL_DIRECTION,DIO_u8_PB4_INITIAL_DIRECTION,
	                    DIO_u8_PB3_INITIAL_DIRECTION,DIO_u8_PB2_INITIAL_DIRECTION,DIO_u8_PB1_INITIAL_DIRECTION,DIO_u8_PB0_INITIAL_DIRECTION); 
     
	 DDRC_u8_REG = CONC(DIO_u8_PC7_INITIAL_DIRECTION,DIO_u8_PC6_INITIAL_DIRECTION,DIO_u8_PC5_INITIAL_DIRECTION,DIO_u8_PC4_INITIAL_DIRECTION,
	                    DIO_u8_PC3_INITIAL_DIRECTION,DIO_u8_PC2_INITIAL_DIRECTION,DIO_u8_PC1_INITIAL_DIRECTION,DIO_u8_PC0_INITIAL_DIRECTION); 
     
	 DDRD_u8_REG = CONC(DIO_u8_PD7_INITIAL_DIRECTION,DIO_u8_PD6_INITIAL_DIRECTION,DIO_u8_PD5_INITIAL_DIRECTION,DIO_u8_PD4_INITIAL_DIRECTION,
	                    DIO_u8_PD3_INITIAL_DIRECTION,DIO_u8_PD2_INITIAL_DIRECTION,DIO_u8_PD1_INITIAL_DIRECTION,DIO_u8_PD0_INITIAL_DIRECTION); 
    /*Initial values for pins */
     PORTA_u8_REG = CONC(DIO_u8_PA7_INITIAL_VALUE,DIO_u8_PA6_INITIAL_VALUE,DIO_u8_PA5_INITIAL_VALUE,DIO_u8_PA4_INITIAL_VALUE,
	                     DIO_u8_PA3_INITIAL_VALUE,DIO_u8_PA2_INITIAL_VALUE,DIO_u8_PA1_INITIAL_VALUE,DIO_u8_PA0_INITIAL_VALUE); 
																											   
	 PORTB_u8_REG = CONC(DIO_u8_PB7_INITIAL_VALUE,DIO_u8_PB6_INITIAL_VALUE,DIO_u8_PB5_INITIAL_VALUE,DIO_u8_PB4_INITIAL_VALUE,
	                     DIO_u8_PB3_INITIAL_VALUE,DIO_u8_PB2_INITIAL_VALUE,DIO_u8_PB1_INITIAL_VALUE,DIO_u8_PB0_INITIAL_VALUE); 
																											   
	 PORTC_u8_REG = CONC(DIO_u8_PC7_INITIAL_VALUE,DIO_u8_PC6_INITIAL_VALUE,DIO_u8_PC5_INITIAL_VALUE,DIO_u8_PC4_INITIAL_VALUE,
	                     DIO_u8_PC3_INITIAL_VALUE,DIO_u8_PC2_INITIAL_VALUE,DIO_u8_PC1_INITIAL_VALUE,DIO_u8_PC0_INITIAL_VALUE); 
																											   
	 PORTD_u8_REG = CONC(DIO_u8_PD7_INITIAL_VALUE,DIO_u8_PD6_INITIAL_VALUE,DIO_u8_PD5_INITIAL_VALUE,DIO_u8_PD4_INITIAL_VALUE,
	                     DIO_u8_PD3_INITIAL_VALUE,DIO_u8_PD2_INITIAL_VALUE,DIO_u8_PD1_INITIAL_VALUE,DIO_u8_PD0_INITIAL_VALUE);

}

u8 MDIO_u8SetPinDirection (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinDirection)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	/* Check 1- Valid Port  ID
	         2- Valid Pin ID
			 3- Valid Pin Direction */
    if((Copy_u8PortID <= DIO_u8_PORTD) && (Copy_u8PinID <= DIO_u8_PIN7) && ((Copy_u8PinDirection == DIO_u8_INPUT) || (Copy_u8PinDirection == DIO_u8_OUTPUT)))
	{
		switch(Copy_u8PortID)
		{
			case DIO_u8_PORTA:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRA_u8_REG,Copy_u8PinID);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRA_u8_REG,Copy_u8PinID);
				break;
			}
			break;
			case DIO_u8_PORTB:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRB_u8_REG,Copy_u8PinID);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRB_u8_REG,Copy_u8PinID);
				break;
			}
			break;
			case DIO_u8_PORTC:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRC_u8_REG,Copy_u8PinID);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRC_u8_REG,Copy_u8PinID);
				break;
			}
			break;
			case DIO_u8_PORTD:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRD_u8_REG,Copy_u8PinID);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRD_u8_REG,Copy_u8PinID);
				break;
			}
			break;
		}
	}
	else
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}
	return Local_u8ReturnState;
}
u8 MDIO_u8SetPinValue     (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	  if((Copy_u8PortID <= DIO_u8_PORTD)  && (Copy_u8PinID <= DIO_u8_PIN7) && ((Copy_u8PinValue == DIO_u8_HIGH) || (Copy_u8PinValue == DIO_u8_LOW)))
	  {
		  switch (Copy_u8PortID)
		  {
			  case DIO_u8_PORTA:
			     switch(Copy_u8PinValue)
				 {
					case DIO_u8_HIGH:
					 SET_BIT(PORTA_u8_REG,Copy_u8PinID);
					break;
					case DIO_u8_LOW:
					 CLR_BIT(PORTA_u8_REG,Copy_u8PinID);
					break;   
				 }
			   break;
			   case DIO_u8_PORTB:
			     switch(Copy_u8PinValue)
				  {
					case DIO_u8_HIGH:
					 SET_BIT(PORTB_u8_REG,Copy_u8PinID);
					break;
					case DIO_u8_LOW:
					 CLR_BIT(PORTB_u8_REG,Copy_u8PinID);
					break;
				  }
			   break;
			   case DIO_u8_PORTC:
			     switch(Copy_u8PinValue)
				  {
					case DIO_u8_HIGH:
					 SET_BIT(PORTC_u8_REG,Copy_u8PinID);
					break;
					case DIO_u8_LOW:
					 CLR_BIT(PORTC_u8_REG,Copy_u8PinID);
					break;
				  }
			   break;
			   case DIO_u8_PORTD:
			     switch(Copy_u8PinValue)
				  { 
					case DIO_u8_HIGH:
					 SET_BIT(PORTD_u8_REG,Copy_u8PinID);
					break;
					case DIO_u8_LOW:
					 CLR_BIT(PORTD_u8_REG,Copy_u8PinID);
					break;
			   	  }
			   break;
		   }
	  }
	  else
	  {
	      Local_u8ReturnState = STD_TYPES_NOK;
	  }
	return Local_u8ReturnState;
}
u8 MDIO_u8GetPinValue     (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 * Copy_pu8ReturnedPinValue)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	if((Copy_u8PortID <= DIO_u8_PORTD)  && (Copy_u8PinID <= DIO_u8_PIN7) && (Copy_pu8ReturnedPinValue != NULL))
	{
		switch (Copy_u8PortID)
		{
			case DIO_u8_PORTA: 
			   if(GET_BIT(PINA_u8_REG,Copy_u8PinID)== 0)
			   {
				   *Copy_pu8ReturnedPinValue = DIO_u8_LOW;
			   }
			   else if(GET_BIT(PINA_u8_REG,Copy_u8PinID)!=0)
			   {
				   *Copy_pu8ReturnedPinValue =DIO_u8_HIGH;
			   }
			break;
			case DIO_u8_PORTB: 
			   if(GET_BIT(PINB_u8_REG,Copy_u8PinID)== 0)
			    {
				   *Copy_pu8ReturnedPinValue = DIO_u8_LOW;
			   }
			   else if(GET_BIT(PINB_u8_REG,Copy_u8PinID)!=0)
			   {
				   *Copy_pu8ReturnedPinValue =DIO_u8_HIGH;
			   }
			break;
			case DIO_u8_PORTC: 
			   if(GET_BIT(PINC_u8_REG,Copy_u8PinID)== 0)
			   {
				   *Copy_pu8ReturnedPinValue = DIO_u8_LOW;
			   }
			   else if(GET_BIT(PINC_u8_REG,Copy_u8PinID)!=0)
			   {
				   *Copy_pu8ReturnedPinValue =DIO_u8_HIGH;
			   }
			break;
			case DIO_u8_PORTD: 
			   if(GET_BIT(PIND_u8_REG,Copy_u8PinID)== 0)
			   {
				   *Copy_pu8ReturnedPinValue = DIO_u8_LOW;
			   }
			   else if(GET_BIT(PIND_u8_REG,Copy_u8PinID)!=0)
			   {
				   *Copy_pu8ReturnedPinValue =DIO_u8_HIGH;
			   }
			break;
		}
	}
	else
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}
	return Local_u8ReturnState;
}
u8 MDIO_u8SetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortDirection )
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	if((Copy_u8PortID <= DIO_u8_PORTD) && ((Copy_u8PortDirection == DIO_u8_OUTPUT) || (Copy_u8PortDirection == DIO_u8_INPUT)))
	{
		switch(Copy_u8PortID)
		{
			case DIO_u8_PORTA:
			switch(Copy_u8PortDirection)
			{
				case DIO_u8_INPUT: DDRA_u8_REG = 0x00;break;
				case DIO_u8_OUTPUT:DDRA_u8_REG = 0xFF;break;
			}
			break;
			case DIO_u8_PORTB:
			switch(Copy_u8PortDirection)
			{
				case DIO_u8_INPUT: DDRB_u8_REG = 0x00;break;
				case DIO_u8_OUTPUT:DDRB_u8_REG = 0xFF;break;
			}
			break;
			case DIO_u8_PORTC:
			switch(Copy_u8PortDirection)
			{
				case DIO_u8_INPUT: DDRC_u8_REG = 0x00;break;
				case DIO_u8_OUTPUT:DDRC_u8_REG = 0xFF;break;
			}
			break;
			case DIO_u8_PORTD:
			switch(Copy_u8PortDirection)
			{
				case DIO_u8_INPUT: DDRD_u8_REG = 0x00;break;
				case DIO_u8_OUTPUT:DDRD_u8_REG = 0xFF;break;
			}
			break;
		}
	}
	else
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}
	return Local_u8ReturnState;
}

u8 MDIO_u8SetPortValue    (u8 Copy_u8PortID, u8 Copy_u8PortValue)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	switch(Copy_u8PortID)
	{
		case DIO_u8_PORTA:PORTA_u8_REG = Copy_u8PortValue; break;
		case DIO_u8_PORTB:PORTB_u8_REG = Copy_u8PortValue; break;
		case DIO_u8_PORTC:PORTC_u8_REG = Copy_u8PortValue; break;
		case DIO_u8_PORTD:PORTD_u8_REG = Copy_u8PortValue; break;
		default : Local_u8ReturnState = STD_TYPES_NOK;
	}
	return Local_u8ReturnState;
}

u8 MDIO_u8Set4PinsValue    (u8 Copy_u8PortID, u8 Copy_u8PinStart, u8 Copy_u8PortValue)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;

	if(Copy_u8PinStart<=4)
	{
		switch(Copy_u8PortID)
		{
		case DIO_u8_PORTA:
			PORTA_u8_REG&=(~(0b00001111<<Copy_u8PinStart));
			PORTA_u8_REG|=(Copy_u8PortValue<<Copy_u8PinStart);
			break;
		case DIO_u8_PORTB:
			PORTB_u8_REG&=(~(0b00001111<<Copy_u8PinStart));
			PORTB_u8_REG|=(Copy_u8PortValue<<Copy_u8PinStart);
			break;
		case DIO_u8_PORTC:
			PORTC_u8_REG&=(~(0b00001111<<Copy_u8PinStart));
			PORTC_u8_REG|=(Copy_u8PortValue<<Copy_u8PinStart);
			break;
		case DIO_u8_PORTD:

			PORTD_u8_REG&=(~(0b00001111<<Copy_u8PinStart));
			PORTD_u8_REG|=(Copy_u8PortValue<<Copy_u8PinStart);
			break;


		}
	}
	else
		{
			Local_u8ReturnState = STD_TYPES_NOK;
		}
	return Local_u8ReturnState;

}


u8 MDIO_u8GetPortValue    (u8 Copy_u8PortID, u8 * Copy_pu8ReturnedPortValue)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	if(Copy_pu8ReturnedPortValue != NULL)
	{
		switch(Copy_u8PortID)
		{
		   case DIO_u8_PORTA: *Copy_pu8ReturnedPortValue = PINA_u8_REG; break;
		   case DIO_u8_PORTB: *Copy_pu8ReturnedPortValue = PINB_u8_REG; break;
		   case DIO_u8_PORTC: *Copy_pu8ReturnedPortValue = PINC_u8_REG; break;
		   case DIO_u8_PORTD: *Copy_pu8ReturnedPortValue = PIND_u8_REG; break;
		   default : Local_u8ReturnState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}
	return Local_u8ReturnState;
}
