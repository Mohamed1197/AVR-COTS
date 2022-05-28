/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 25/9/2020           ********************/
/**************** SWC     :     TMR             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TMR_interface.h"
#include "TMR_private.h"
#include "TMR_config.h"




static void (*TMR_pfTimer0OVF)(void) = NULL;
static void (*TMR_pfTimer0CTC)(void) = NULL;

static void (*TMR_pfTimer1CTC)(void) = NULL;

volatile static u16 TMR_u16OnPeriod , TMR_u16OffPeriod , TMR1_ISR_CTC_Counter = 0;

void TMR_voidTimer0Init(void)
{

 /* Timer0 Mode IF Selection */
#if (TIMER0_MODE == NORMAL_MODE)
	{
      CLR_BIT(TMR_u8_TCCR0_REG,6);
      CLR_BIT(TMR_u8_TCCR0_REG,3);
      TMR_u8_TCNT0_REG = PRELOAD_VALUE ;
      #if (TIMER_PIE == ENABLE_TIMER0_PIE)
	    {
		  SET_BIT(TMR_u8_TIMSK_REG,0);
	    }
      #endif
	}
#elif (TIMER0_MODE == CTC_MODE)
	{
	  CLR_BIT(TMR_u8_TCCR0_REG,6);
	  SET_BIT(TMR_u8_TCCR0_REG,3);
	  TMR_u8_OCR0_REG = COMPARE_MATCH_VALUE;
      #if (TIMER_PIE == ENABLE_TIMER0_PIE)
	   {
		  SET_BIT(TMR_u8_TIMSK_REG,1);
	   }
      #endif
	}
#elif (TIMER0_MODE == FAST_PWM)
	{
		SET_BIT(TMR_u8_TCCR0_REG,6);
		SET_BIT(TMR_u8_TCCR0_REG,3);
	}
#elif (TIMER0_MODE == PHASE_CORRECT_PWM)
	{
	   SET_BIT(TMR_u8_TCCR0_REG,6);
	   CLR_BIT(TMR_u8_TCCR0_REG,3);
	}

#endif

	 /* Timer0 Compare Output Mode IF Selection */
#if (TMR0_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED)
{
	CLR_BIT(TMR_u8_TCCR0_REG,5);
 	CLR_BIT(TMR_u8_TCCR0_REG,4);
}
#elif (TMR0_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE)
{
	CLR_BIT(TMR_u8_TCCR0_REG,5);
	SET_BIT(TMR_u8_TCCR0_REG,4);
}
#elif ((TMR0_COMPARE_OUTPUT_MODE == CLEAR_OC0_ON_COMPARE) || (TMR0_COMPARE_OUTPUT_MODE == NON_INVERTING_PWM))
{
	SET_BIT(TMR_u8_TCCR0_REG,5);
	CLR_BIT(TMR_u8_TCCR0_REG,4);
}
#elif ((TMR0_COMPARE_OUTPUT_MODE == SET_OC0_ON_COMPARE) || (TMR0_COMPARE_OUTPUT_MODE == INVERTING_PWM))
{
	SET_BIT(TMR_u8_TCCR0_REG,5);
	SET_BIT(TMR_u8_TCCR0_REG,4);
}
#endif

/* Timer0 Prescaler Value IF Selection */
#if (TMR0_PRESCALER_VALUE == TIMER_OFF)
	{
		 CLR_BIT(TMR_u8_TCCR0_REG,2);
		 CLR_BIT(TMR_u8_TCCR0_REG,1);
		 CLR_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == NO_PRESCALING)
	{
		 CLR_BIT(TMR_u8_TCCR0_REG,2);
		 CLR_BIT(TMR_u8_TCCR0_REG,1);
		 SET_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == CLOCK_8)
	{
		 CLR_BIT(TMR_u8_TCCR0_REG,2);
		 SET_BIT(TMR_u8_TCCR0_REG,1);
		 CLR_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == CLOCK_64)
	{
		 CLR_BIT(TMR_u8_TCCR0_REG,2);
		 SET_BIT(TMR_u8_TCCR0_REG,1);
		 SET_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == CLOCK_256)
	{
		 SET_BIT(TMR_u8_TCCR0_REG,2);
		 CLR_BIT(TMR_u8_TCCR0_REG,1);
		 CLR_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == CLOCK_1024)
	{
		 SET_BIT(TMR_u8_TCCR0_REG,2);
		 CLR_BIT(TMR_u8_TCCR0_REG,1);
		 SET_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == CLOCK_FALLING_EDGE)
	{
		 SET_BIT(TMR_u8_TCCR0_REG,2);
		 SET_BIT(TMR_u8_TCCR0_REG,1);
		 CLR_BIT(TMR_u8_TCCR0_REG,0);
	}
#elif (TMR0_PRESCALER_VALUE == CLOCK_RISING_EDGE)
	{
		 SET_BIT(TMR_u8_TCCR0_REG,2);
		 SET_BIT(TMR_u8_TCCR0_REG,1);
		 SET_BIT(TMR_u8_TCCR0_REG,0);
	}
#endif

 // /* Set Preload Value */
 // TMR_u8_TCNT0_REG = 192;
 //
 // /* Enable PIE of OVF */
 // SET_BIT(TMR_u8_TIMSK_REG,0);
 //
 // /* Prescaler => 8 */
 // CLR_BIT(TMR_u8_TCCR0_REG,2);
 // SET_BIT(TMR_u8_TCCR0_REG,1);
 // CLR_BIT(TMR_u8_TCCR0_REG,0);

	
	
//	/* Select Moe Of Timer => CTC Mode */
//	CLR_BIT(TMR_u8_TCCR0_REG,6);
//	SET_BIT(TMR_u8_TCCR0_REG,3);
//
//	/* Set Compare Match Register */
//	 TMR_u8_OCR0_REG = COMPARE_MATCH_VALUE;
//
//	  /* Enable PIE of CTC */
//	  SET_BIT(TMR_u8_TIMSK_REG,1);
//
//	  /* Prescaler => 8 */
//	  CLR_BIT(TMR_u8_TCCR0_REG,2);
//	  SET_BIT(TMR_u8_TCCR0_REG,1);
//	  CLR_BIT(TMR_u8_TCCR0_REG,0);


	
//		/* Select Mode Of Timer => Fast PWM */
//		SET_BIT(TMR_u8_TCCR0_REG,6);
//		SET_BIT(TMR_u8_TCCR0_REG,3);
//	   /* Select Action on OC0 Pin => Non Inverting */
//   	SET_BIT(TMR_u8_TCCR0_REG,5);
//	    CLR_BIT(TMR_u8_TCCR0_REG,4);
//
//	    /* Prescaler => 8 */
//	    CLR_BIT(TMR_u8_TCCR0_REG,2);
//      SET_BIT(TMR_u8_TCCR0_REG,1);
//      CLR_BIT(TMR_u8_TCCR0_REG,0);

//
//		/* Select Mode Of Timer => Phase Correct PWM */
//		SET_BIT(TMR_u8_TCCR0_REG,6);
//		CLR_BIT(TMR_u8_TCCR0_REG,3);
//
//		/* Select Action on OC0 Pin => Non Inverting */
//		SET_BIT(TMR_u8_TCCR0_REG,5);
//		CLR_BIT(TMR_u8_TCCR0_REG,4);
//
//		/* Prescaler => 8 */
//   	CLR_BIT(TMR_u8_TCCR0_REG,2);
//	    SET_BIT(TMR_u8_TCCR0_REG,1);
//	    CLR_BIT(TMR_u8_TCCR0_REG,0);

}

u8   TMR_u8Timer1GetCounterValue(u16 * Copy_pu16CounterValue)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu16CounterValue != NULL)
	{
		*Copy_pu16CounterValue = TMR_u16_TCNT1_REG;
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

void TMR_voidTimer1Init(void)
{
//	/* Timer1 Select Mode 14 => ICR1 top Value */
//	SET_BIT(TMR_u8_TCCR1A_REG,1);
//	CLR_BIT(TMR_u8_TCCR1A_REG,0);
//	SET_BIT(TMR_u8_TCCR1B_REG,4);
//	SET_BIT(TMR_u8_TCCR1B_REG,3);
//
//	/* Channel A => NON Inverting */
//	SET_BIT(TMR_u8_TCCR1A_REG,7);
//	CLR_BIT(TMR_u8_TCCR1A_REG,6);
//
//	/* Set Max Value */
//	TMR_u16_ICR1_REG = 19999;
//
//	/* Set Prescaler => 8 */
//	CLR_BIT(TMR_u8_TCCR1B_REG,2);
//	SET_BIT(TMR_u8_TCCR1B_REG,1);
//	CLR_BIT(TMR_u8_TCCR1B_REG,0);

//	/* Select Mode of Timer1 => Normal Mode */
//	    CLR_BIT(TMR_u8_TCCR1A_REG,1);
//		CLR_BIT(TMR_u8_TCCR1A_REG,0);
//		CLR_BIT(TMR_u8_TCCR1B_REG,4);
//		CLR_BIT(TMR_u8_TCCR1B_REG,3);
//
//		/* Start Timer Prescaler  => 8 */
//	   	CLR_BIT(TMR_u8_TCCR0_REG,2);
//	    SET_BIT(TMR_u8_TCCR0_REG,1);
//	    CLR_BIT(TMR_u8_TCCR0_REG,0);

	 /* Timer1 Mode IF Selection */
#if (TIMER1_MODE == NORMAL_MODE)
	{
         CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
         #if (TIMER1_PIE == ENABLE_TIMER1_PIE)
           {
         	  SET_BIT(TMR_u8_TIMSK_REG,2);
           }
         #endif
	}
#elif(TIMER1_MODE == PHASE_CORRECT_PWM_8BIT)
	{
         CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);

	}
#elif(TIMER1_MODE == PHASE_CORRECT_PWM_9BIT)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == PHASE_CORRECT_PWM_10BIT)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == CTC_OCR1A)
	{
		 CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
	   	 SET_BIT(TMR_u8_TCCR1B_REG,3);
         #if (TIMER1_PIE == ENABLE_TIMER1_PIE)
         {
	         SET_BIT(TMR_u8_TIMSK_REG,4);
         }
#endif
	}
#elif(TIMER1_MODE == FAST_PWM_8BIT)
	{
		 CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
	   	 SET_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == FAST_PWM_9BIT)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
	   	 SET_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == FAST_PWM_10BIT)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
	   	 CLR_BIT(TMR_u8_TCCR1B_REG,4);
	   	 SET_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == PWM_PHASE_FREQUENCY_CORRECT_ICR1)
	{
		 CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
		 TMR_u16_ICR1_REG = ICR1_MAX_VALUE;
	}
#elif(TIMER1_MODE == PWM_PHASE_FREQUENCY_CORRECT_OCR1A)
	{
		 CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == PWM_PHASE_CORRECT_ICR1)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
		 TMR_u16_ICR1_REG = ICR1_MAX_VALUE;
	}
#elif(TIMER1_MODE == PWM_PHASE_CORRECT_OCR1A)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 CLR_BIT(TMR_u8_TCCR1B_REG,3);
	}
#elif(TIMER1_MODE == CTC_ICR1)
	{
		 CLR_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 SET_BIT(TMR_u8_TCCR1B_REG,3);
		 TMR_u16_ICR1_REG = ICR1_MAX_VALUE;
	}
#elif(TIMER1_MODE == FAST_PWM_ICR1)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 CLR_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 SET_BIT(TMR_u8_TCCR1B_REG,3);
		 TMR_u16_ICR1_REG = ICR1_MAX_VALUE;
	}
#elif(TIMER1_MODE == FAST_PWM_OCR1A)
	{
		 SET_BIT(TMR_u8_TCCR1A_REG,1);
		 SET_BIT(TMR_u8_TCCR1A_REG,0);
		 SET_BIT(TMR_u8_TCCR1B_REG,4);
		 SET_BIT(TMR_u8_TCCR1B_REG,3);
	}

#endif


	 /* Timer1 Compare Output Mode IF Selection */
	  /*   Channel A     */
#if (TMR1_CHANNELA_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED)
{
	CLR_BIT(TMR_u8_TCCR1A_REG,7);
	CLR_BIT(TMR_u8_TCCR1A_REG,6);
}
#elif (TMR1_CHANNELA_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE)
{
	CLR_BIT(TMR_u8_TCCR1A_REG,7);
	SET_BIT(TMR_u8_TCCR1A_REG,6);
}
#elif ((TMR1_CHANNELA_COMPARE_OUTPUT_MODE == CLEAR_OC0_ON_COMPARE) || (TMR1_CHANNELA_COMPARE_OUTPUT_MODE == NON_INVERTING_PWM))
{
	SET_BIT(TMR_u8_TCCR1A_REG,7);
	CLR_BIT(TMR_u8_TCCR1A_REG,6);
}
#elif ((TMR1_CHANNELA_COMPARE_OUTPUT_MODE == SET_OC0_ON_COMPARE) || (TMR1_CHANNELA_COMPARE_OUTPUT_MODE == INVERTING_PWM))
{
	SET_BIT(TMR_u8_TCCR1A_REG,7);
	SET_BIT(TMR_u8_TCCR1A_REG,6);
}
#endif

      /*   Channel B     */
#if (TMR1_CHANNELB_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED)
{
CLR_BIT(TMR_u8_TCCR1A_REG,5);
CLR_BIT(TMR_u8_TCCR1A_REG,4);
}
#elif (TMR1_CHANNELB_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE)
{
CLR_BIT(TMR_u8_TCCR1A_REG,5);
SET_BIT(TMR_u8_TCCR1A_REG,4);
}
#elif ((TMR1_CHANNELB_COMPARE_OUTPUT_MODE == CLEAR_OC0_ON_COMPARE) || (TMR1_CHANNELB_COMPARE_OUTPUT_MODE == NON_INVERTING_PWM))
{
SET_BIT(TMR_u8_TCCR1A_REG,5);
CLR_BIT(TMR_u8_TCCR1A_REG,4);
}
#elif ((TMR1_CHANNELB_COMPARE_OUTPUT_MODE == SET_OC0_ON_COMPARE) || (TMR1_CHANNELB_COMPARE_OUTPUT_MODE == INVERTING_PWM))
{
SET_BIT(TMR_u8_TCCR1A_REG,5);
SET_BIT(TMR_u8_TCCR1A_REG,4);
}
#endif


/* Timer1 Prescaler Value IF Selection */
#if (TMR1_PRESCALER_VALUE == TIMER_OFF)
	{
		 CLR_BIT(TMR_u8_TCCR1B_REG,2);
		 CLR_BIT(TMR_u8_TCCR1B_REG,1);
		 CLR_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == NO_PRESCALING)
	{
		 CLR_BIT(TMR_u8_TCCR1B_REG,2);
		 CLR_BIT(TMR_u8_TCCR1B_REG,1);
		 SET_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == CLOCK_8)
	{
		 CLR_BIT(TMR_u8_TCCR1B_REG,2);
		 SET_BIT(TMR_u8_TCCR1B_REG,1);
		 CLR_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == CLOCK_64)
	{
		 CLR_BIT(TMR_u8_TCCR1B_REG,2);
		 SET_BIT(TMR_u8_TCCR1B_REG,1);
		 SET_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == CLOCK_256)
	{
		 SET_BIT(TMR_u8_TCCR1B_REG,2);
		 CLR_BIT(TMR_u8_TCCR1B_REG,1);
		 CLR_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == CLOCK_1024)
	{
		 SET_BIT(TMR_u8_TCCR1B_REG,2);
		 CLR_BIT(TMR_u8_TCCR1B_REG,1);
		 SET_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == CLOCK_FALLING_EDGE)
	{
		 SET_BIT(TMR_u8_TCCR1B_REG,2);
		 SET_BIT(TMR_u8_TCCR1B_REG,1);
		 CLR_BIT(TMR_u8_TCCR1B_REG,0);
	}
#elif (TMR1_PRESCALER_VALUE == CLOCK_RISING_EDGE)
	{
		 SET_BIT(TMR_u8_TCCR1B_REG,2);
		 SET_BIT(TMR_u8_TCCR1B_REG,1);
		 SET_BIT(TMR_u8_TCCR1B_REG,0);
	}
#endif


}

void TMR_voidTimer1SetCompareMatchValueChannelA(u16 Copy_u16CompareMatchValue)
{
	TMR_u16_OCR1A_REG = Copy_u16CompareMatchValue;
}

void TMR_voidTimer1CTCCounter(u16 Copy_u16CTCCounter)
{
	TMR1_ISR_CTC_Counter = Copy_u16CTCCounter;
}

void TMR_voidTimer0SetCompareMatchValue(u8 Copy_u8OCRValue)
{
	TMR_u8_OCR0_REG = Copy_u8OCRValue;
}

u8  TMR_u8Timer0OVFSetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8_ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TMR_pfTimer0OVF = Copy_pf;
	}
	else
	{
		Local_u8_ErrorState =STD_TYPES_NOK;
	}
	return Local_u8_ErrorState;
}

u8  TMR_u8Timer0CTCSetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8_ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TMR_pfTimer0CTC = Copy_pf;
	}
	else
	{
		Local_u8_ErrorState =STD_TYPES_NOK;
	}
	return Local_u8_ErrorState;
}

u8  TMR_u8Timer1CTCSetCallBack(void (*Copy_pf)(void))
{
	u8 Local_u8_ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TMR_pfTimer1CTC = Copy_pf;
	}
	else
	{
		Local_u8_ErrorState =STD_TYPES_NOK;
	}
	return Local_u8_ErrorState;
}

void TMR_voidHWICUEnable(void)
{
	/* Select Triggering Interrupt source of ICU = Rising Edge */
	SET_BIT(TMR_u8_TCCR1B_REG,6);

	/* Enable ICU Interrupt */
	SET_BIT(TMR_u8_TIMSK_REG,5);
}

void TMR_voidHWICUDisable(void)
{
	/* Disable ICU Interrupt */
	SET_BIT(TMR_u8_TIMSK_REG,5);

}

u8   TMR_u8GetPWMTotalPeriod(u32 * Copy_pu32TotalPeriod)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu32TotalPeriod != NULL)
	{
		*Copy_pu32TotalPeriod = TMR_u16OnPeriod + TMR_u16OffPeriod;
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

u8   TMR_u8GetPWMDutyCycle(u8 * Copy_pu8DutyCycle)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu8DutyCycle != NULL)
	{
		*Copy_pu8DutyCycle =(u8)((TMR_u16OnPeriod * 100UL)/(TMR_u16OnPeriod + TMR_u16OffPeriod));

		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

u8   TMR_u8GetPWMOnPeriod(u16 * Copy_pu16OnPeriod)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu16OnPeriod != NULL)
	{
		*Copy_pu16OnPeriod = TMR_u16OnPeriod;
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}

/* Prototype of ISR Timer0 OVF */
void __vector_11(void)     __attribute__((signal));
void __vector_11(void)
{
	static u16 Local_u16Counter = 0 ;
	Local_u16Counter++;
	if(Local_u16Counter == 3907)
	{
		/* Set Preload Value */
		TMR_u8_TCNT0_REG = PRELOAD_VALUE;
		/* Reset Counter */
		Local_u16Counter = 0;
		/* Call CallBack Function */
		if(TMR_pfTimer0OVF != NULL)
		{
			TMR_pfTimer0OVF();
		}
	}
}
/* Prototype of ISR Timer0 Compare Match */
void __vector_10(void)     __attribute__((signal));
void __vector_10(void)
{
	static u16 Local_u16Counter = 0 ;
	Local_u16Counter++;
	if(Local_u16Counter == 10000)
	{
		/* Reset Counter */
		Local_u16Counter = 0;
		/* Call CallBack Function */
		if(TMR_pfTimer0CTC != NULL)
		{
			TMR_pfTimer0CTC();
		}
	}
}

/* Prototype of ISR Timer1 ICU */
void __vector_6(void)     __attribute__((signal));
void __vector_6(void)
{
	u16 Local_u16TimerValue = TMR_u16_ICR1_REG;
	static u8 Local_u8Flag = 0;
	static u16 Local_u16OldValue = 0;
	if(Local_u8Flag == 0) /* Rising Edge */
	{
		TMR_u16OffPeriod = Local_u16TimerValue - Local_u16OldValue;
		/* Trigger Source into Falling Edge */
		CLR_BIT(TMR_u8_TCCR1B_REG,6);
		Local_u8Flag = 1;
	}
	else
	{
		TMR_u16OnPeriod = Local_u16TimerValue - Local_u16OldValue;
		/* Trigger Source into Rising Edge */
		SET_BIT(TMR_u8_TCCR1B_REG,6);
		Local_u8Flag = 0;
	}
	Local_u16OldValue = Local_u16TimerValue;
}

/* Prototype of ISR Timer1 Compare Match A */
void __vector_7(void)       __attribute__((signal));
void __vector_7(void)
{
	static u16 Local_u16Counter = 0 ;
	Local_u16Counter++;
	if(TMR1_ISR_CTC_Counter != 0)
	{
	     if(Local_u16Counter == TMR1_ISR_CTC_Counter)
	     {
	     	/* Reset Counter */
	     	Local_u16Counter = 0;
	     	/* Call CallBack Function */
	     	if(TMR_pfTimer1CTC != NULL)
	     	{
	     		TMR_pfTimer1CTC();
	     	}
	     }
	}
	else
	{
     	/* Call CallBack Function */
     	if(TMR_pfTimer1CTC != NULL)
     	{
     		TMR_pfTimer1CTC();
     	}
	}

}

