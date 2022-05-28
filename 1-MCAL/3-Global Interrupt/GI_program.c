/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 12/9/2020           ********************/
/**************** SWC     :     GI              ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GI_interface.h"
/* Defination of SREG */
#define GI_u8_SREG              *((volatile u8*)0x5F)


void GI_voidEnable (void)
{
	SET_BIT(GI_u8_SREG,7);
}

void GI_voidDisable(void)
{
	CLR_BIT(GI_u8_SREG,7);
}