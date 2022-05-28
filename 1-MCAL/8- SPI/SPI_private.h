/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 10/10/2020          ********************/
/**************** SWC     :     SPI             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#define SPI_u8_MASTER_MODE                     0
#define SPI_u8_SLAVE_MODE                      1

#define SPI_u8_SPDR_REG                *((volatile u8*)0x2F)
#define SPI_u8_SPSR_REG                *((volatile u8*)0x2E)
#define SPI_u8_SPCR_REG                *((volatile u8*)0x2D)



#endif