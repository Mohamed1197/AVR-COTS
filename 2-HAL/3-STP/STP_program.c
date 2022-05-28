/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 07/9/2020           ********************/
/**************** SWC     :   STP               ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/

/*Lib*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include<util/delay.h>
/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"

u16 i;
u8 Local_u8ErrorState;
u8 Stepper_u8Rotation(u16 Copy_u16Angle , u8 Copy_u8Direction)
{
	if((Copy_u16Angle <=360))
	{
	    Local_u8ErrorState = STD_TYPES_OK;
	    u32 NumberofSteps = (u32)((Copy_u16Angle * 2048UL)/360);
		NumberofSteps = NumberofSteps / 4 ;
		
		if(Copy_u8Direction == AntiClockwise)
		{
		for(i=0; i < NumberofSteps ; i++)
		{
			
		//STEP 1
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_HIGH);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
		_delay_ms(5);

        //STEP 2
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_HIGH);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
		_delay_ms(5);

        //STEP 3
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_HIGH);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
		_delay_ms(5);

        //STEP 4
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_HIGH);
		_delay_ms(5);

		}
		}
		else if(Copy_u8Direction == Clockwise)
		{
		for(i=0; i < NumberofSteps ; i++)
		{

		//STEP 1
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_HIGH);
		_delay_ms(5);

        //STEP 2
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_HIGH);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
		_delay_ms(5);

        //STEP 3
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_HIGH);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
		_delay_ms(5);

        //STEP 4
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_HIGH);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
		_delay_ms(5);
		}
		}
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);

		
		
		
		
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

void Stepper_voidStop(void)
{
	DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
	DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
	DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
	DIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);

}

void DC_voidRotation(u8 Copy_u8Direction)
{
	if(Copy_u8Direction == Clockwise)
	{
		DIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_REVERSE,DIO_u8_LOW);
		DIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_FORWARD,DIO_u8_HIGH);
	}
	else if(Copy_u8Direction == AntiClockwise)
	{
		DIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_FORWARD,DIO_u8_LOW);
		DIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_REVERSE,DIO_u8_HIGH);
	}


}

void DC_voidStop(void)
{
	DIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_FORWARD,DIO_u8_LOW);
	DIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_REVERSE,DIO_u8_LOW);
}
