/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 02/10/2020          ********************/
/**************** SWC     :     WDT             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_interface.h"

#define WDT_u8_WDTCR_REG             *((volatile u8 *)0x41)

void WDT_voidEnable(void)
{
	/* Select Prescaler => 2.1 Sec */
	WDT_u8_WDTCR_REG =0b00001111;
}

void WDT_voidDisable(void)
{
	/* Turn OFF Enable */
	WDT_u8_WDTCR_REG |= (1<<4)|(1<<3);
	
	WDT_u8_WDTCR_REG = 0x00;
}