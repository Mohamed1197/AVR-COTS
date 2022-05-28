#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "EXTI_interface.h"
#include "TMR_interface.h"

/* HAL */
#include "SWICU_interface.h"
#include "SWICU_config.h"
#include "SWICU_private.h"

static u16 SWICU_u16OnPeriod, SWICU_u16OffPeriod;

void SWICU_voidEnable(void)
{
	/* Set CallBack Function */
	EXTI_u8SetCallBack(&SWICU_voidEXTICallBack,EXTI_u8_INT0);
	/* Enable EXTI0 */
	EXTI_u8Enable(EXTI_u8_INT0,EXTI_u8_RISING_EDGE);
}
void SWICU_voidDisable(void)
{
	EXTI_u8Disable(EXTI_u8_INT0);
}

u8   SWICU_u8GetTotalPeriod(u32 * Copy_u32TotalPeriod)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_u32TotalPeriod != NULL)
	{
		*Copy_u32TotalPeriod = SWICU_u16OnPeriod + SWICU_u16OffPeriod;
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

u8   SWICU_u8GetDutyCycle(u8 * Copy_u8DutyCycle)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_u8DutyCycle != NULL)
	{
		*Copy_u8DutyCycle =(u8)((SWICU_u16OnPeriod * 100UL)/(SWICU_u16OnPeriod + SWICU_u16OffPeriod));
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

u8   SWICU_u8GetOnPeriod(u16 * Copy_u8OnPeriod)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_u8OnPeriod != NULL)
	{
		*Copy_u8OnPeriod = SWICU_u16OnPeriod;
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

static void SWICU_voidEXTICallBack(void)
{
	u16 Local_u16TimerValue;
	static u8 Local_u8Flag = 0;
	static u16 Local_u16OldValue =0;
	/* Read Timer Value */
	TMR_u8Timer1GetCounterValue(&Local_u16TimerValue);
	if(Local_u8Flag == 0) /* Rising Edge */
	{
		SWICU_u16OffPeriod = Local_u16TimerValue - Local_u16OldValue;
		/* Change Sense Control into Falling Edge */
		EXTI_u8Enable(EXTI_u8_INT0,EXTI_u8_FALLING_EDGE);
		/* Change Flag into Falling Edge */
		Local_u8Flag = 1;
	}
	else/* Falling Edge */
	{
		SWICU_u16OnPeriod = Local_u16TimerValue - Local_u16OldValue;
		/* Change Sense Control into Rising Edge */
		EXTI_u8Enable(EXTI_u8_INT0,EXTI_u8_RISING_EDGE);
		/* Change Flag into Rising Edge */
		Local_u8Flag = 0;
	}
	Local_u16OldValue = Local_u16TimerValue;


}
