/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 23/10/2020          ********************/
/**************** SWC     :     RTOS            ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef RTO_INTERFACE_H
#define RTO_INTERFACE_H

u8     RTO_u8CreateTask(u8 Copy_u8Priority, u8 Copy_u8Periodicity, u8 Copy_u8FirstDelay, void(*Copy_pf)(void));

void   RTO_voidScheduler(void);

#endif