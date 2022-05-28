/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 11/9/2020           ********************/
/**************** SWC     :   EXTI              ********************/
/**************** Version :   1.0               ********************/
/*******************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
/* Macros for External Interrupt Index */
#define EXTI_u8_INT0                      0
#define EXTI_u8_INT1                      1
#define EXTI_u8_INT2                      2

/* Macros For Edge of Interrupts */
#define EXTI_u8_FALLING_EDGE              0
#define EXTI_u8_RISING_EDGE               1
#define EXTI_u8_ANY_LOGICAL_CHANGE        2
#define EXTI_u8_LOW_LEVEL                 3


u8 EXTI_u8Enable (u8 Copy_u8_EXTIIndex , u8 Copy_u8EXTIEdge);

u8 EXTI_u8Disable(u8 Copy_u8_EXTIIndex);

u8 EXTI_u8SetCallBack(void (*Copy_pf)(void),u8 Copy_u8CallBackIndex);

#endif
