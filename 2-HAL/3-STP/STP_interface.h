/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 07/9/2020           ********************/
/**************** SWC     :   STP               ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/
#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

#define Clockwise                     0
#define AntiClockwise                 1

u8 Stepper_u8Rotation(u16 Copy_u16Angle , u8 Copy_u8Direction);

void Stepper_voidStop(void);

void DC_voidRotation(u8 Copy_u8Direction);

void DC_voidStop(void);

#endif
