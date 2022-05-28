/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 18/9/2020           ********************/
/**************** SWC     :     ADC             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/

/* Lib */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* Mcal */
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/* Global Pointer To Function */
static void (*ADC_pfNotification)(u16) = NULL;

static u8 ADC_u8BusyFlag =0;

void ADC_voidInit(void)
{
//    /* 1- Select Vref = AVCC */
//    CLR_BIT(ADC_u8_ADMUX_REG,7);
//    SET_BIT(ADC_u8_ADMUX_REG,6);
//    /* 2- Right Adjust */
//	CLR_BIT(ADC_u8_ADMUX_REG,5);
//    /* 3- Disable AutoTrigger */
//	CLR_BIT(ADC_u8_ADCSRA_REG,5);
//    /* 4- Clock/64  */
//	SET_BIT(ADC_u8_ADCSRA_REG,2);
//	SET_BIT(ADC_u8_ADCSRA_REG,1);
//  CLR_BIT(ADC_u8_ADCSRA_REG,0);
//    /* 5- Enable ADC periphieral */
//	SET_BIT(ADC_u8_ADCSRA_REG,7);


	/* 1- Select Vref */
#if(ADC_VREF == AREF)
	{
	   CLR_BIT(ADC_u8_ADMUX_REG,7);
	   CLR_BIT(ADC_u8_ADMUX_REG,6);
	}
#elif(ADC_VREF == AVCC)
	{
	    CLR_BIT(ADC_u8_ADMUX_REG,7);
	    SET_BIT(ADC_u8_ADMUX_REG,6);
	}
#elif(ADC_VREF == INTERNAL)
	{
		SET_BIT(ADC_u8_ADMUX_REG,7);
	    SET_BIT(ADC_u8_ADMUX_REG,6);
	}
#endif

	/* ADC Adjust Result */
#if(ADJUST_RESULT == RIGHT_ADJUST)
	{
		CLR_BIT(ADC_u8_ADMUX_REG,5);
	}
#elif(ADJUST_RESULT == LEFT_ADJUST)
	{
		SET_BIT(ADC_u8_ADMUX_REG,5);
	}
#endif

	/* AutoTrigger */
#if(ADC_AUTO_TRIG_MODE == ADC_AUTO_TRIG_ENABLE)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,5);
	}
#elif(ADC_AUTO_TRIG_MODE == ADC_AUTO_TRIG_DISABLE)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,5);
	}
#endif

	/* ADC CLOCK */
#if(ADC_CLOCK == CLOCK_2)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,2);
		CLR_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_4)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    CLR_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_8)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_16)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		CLR_BIT(ADC_u8_ADCSRA_REG,1);
	    CLR_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_32)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		CLR_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_64)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    CLR_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_128)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#endif

	/* ADC Enable Peripheral */
#if(ADC_MODE == ADC_ENABLE)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,7);
	}
#elif(ADC_MODE == ADC_DISABLE)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,7);
	}
#endif
}

u8 ADC_u8GetDigitalValueSunchNonBlocking(u8 Copy_u8ChannelNb,u16* Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u8TimeOutCounter = 0;
	if((Copy_u8ChannelNb < 32) && (Copy_pu16DigitalValue != NULL))
	{
		/* Clear MUX 4..0 Bits */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		/* Wait Till Flag = 1 */
		while((GET_BIT(ADC_u8_ADCSRA_REG,4)==0) && (Local_u8TimeOutCounter < ADC_u8_TIME_OUT_MAX_VALUE))
		{
			Local_u8TimeOutCounter ++;
		}
		//while(!GET_BIT(ADC_u8_ADCSRA_REG,4));
		if(Local_u8TimeOutCounter >= ADC_u8_TIME_OUT_MAX_VALUE)
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
		else
		{
			/* Read Digital Value */
			*Copy_pu16DigitalValue = ADC_u16_ADC_REG;
			/* Clear Flag */
			SET_BIT(ADC_u8_ADCSRA_REG,4);
		}

	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 ADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNb,void(*Copy_PfNotification)(u16))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_u8ChannelNb < 32) && (*Copy_PfNotification != NULL) && (ADC_u8BusyFlag == 0) )
	{
		/* ADC is Busy */
		ADC_u8BusyFlag = 1;
		/* Updating Global Pointer to a Function With the Notification Function */
		ADC_pfNotification = Copy_PfNotification;
		/* Enable Interrupt PIE */
		SET_BIT(ADC_u8_ADCSRA_REG,3);
		/* Clear MUX 4..0 Bits */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 ADC_u8ReadADCRegister(u16 * Copy_pu16ADCRegValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pu16ADCRegValue !=NULL)
	{
	    *Copy_pu16ADCRegValue = ADC_u16_ADC_REG;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/* Prototype of ADC ISR */
void __vector_16(void)   __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotification != NULL)
	{
		/* Clear PIE */
		CLR_BIT(ADC_u8_ADCSRA_REG,3);
		/* Calling Notification Function */
		ADC_pfNotification(ADC_u16_ADC_REG);
		/* Clear Busy Flag */
		ADC_u8BusyFlag =0;
	}
}
