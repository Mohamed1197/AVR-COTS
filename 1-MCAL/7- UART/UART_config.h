/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 09/10/2020          ********************/
/**************** SWC     :     UART            ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef UART_CONFIG_H
#define UART_CONFIG_H

/* Select Baud Rate = 9600  */
#define UBRR_VALUE                51


/* UART TX Enable \ Disable  */
#define  TX_ENABLE                0
#define  TX_DISABLE               1
#define  TX_MODE               TX_ENABLE


/* UART RX Enable \ Disable  */
#define  RX_ENABLE                0
#define  RX_DISABLE               1
#define  RX_MODE               RX_ENABLE


/* Character Size */
#define CHARCTER_5_BIT                 0
#define CHARCTER_6_BIT                 1
#define CHARCTER_7_BIT                 2
#define CHARCTER_8_BIT                 3
#define CHARCTER_9_BIT                 4
#define CHARACTER_SIZE            CHARCTER_8_BIT


/* Select UART Operation Mode */
#define SYNC_OPERATION                 0
#define ASYNC_OPERATION                1
#define OPERATION_MODE            ASYNC_OPERATION


/* Parity Bit Mode */
#define DISABLED                    0
#define EVEN_PARITY                 1
#define ODD_PARITY                  2
#define PARITY_MODE              DISABLED


/* Stop Bits */
#define STOP_1_BIT                    0
#define STOP_2_BIT                    1
#define STOP_BITS                 STOP_2_BIT


/* Rx max Time Out  */
#define RX_MAX_TIME_OUT           50000


#endif
