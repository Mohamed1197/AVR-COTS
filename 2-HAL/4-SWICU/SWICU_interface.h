/*
 * SWICU_interface.h
 *
 *  Created on: Oct 3, 2020
 *      Author: mhafi
 */

#ifndef SWICU_INTERFACE_H_
#define SWICU_INTERFACE_H_

void SWICU_voidEnable(void);

void SWICU_voidDisable(void);

u8   SWICU_u8GetTotalPeriod(u32 * Copy_u32TotalPeriod);

u8   SWICU_u8GetDutyCycle(u8 * Copy_u8DutyCycle);

u8   SWICU_u8GetOnPeriod(u16 * Copy_u8OnPeriod);


#endif /* SWICU_INTERFACE_H_ */
