/*******************************************************************/
/**************** Name    : Mohamed Ahmed Hafiz ********************/
/**************** Date    : 10/10/2020          ********************/
/**************** SWC     :     SPI             ********************/
/**************** Version :     1.0             ********************/
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void SPI_voidInit(void)
{
	#if (SPI_u8_MODE == SPI_u8_MASTER_MODE)
	/* Data Order = MSB First */
	CLR_BIT(SPI_u8_SPCR_REG,5);
	/* Select Master Mode */
	SET_BIT(SPI_u8_SPCR_REG,4);
    /* Clock Polatity Falling/Rising  Clock Phase Setup/Sample */
	SET_BIT(SPI_u8_SPCR_REG,3);
	SET_BIT(SPI_u8_SPCR_REG,2);
	/* Select Clock Fosc/64 */
	SET_BIT(SPI_u8_SPCR_REG,1);
	CLR_BIT(SPI_u8_SPCR_REG,0);
		
	#elif (SPI_u8_MODE == SPI_u8_SLAVE_MODE)
	/* Data Order = MSB First */
	CLR_BIT(SPI_u8_SPCR_REG,5);
	/* Select Master Mode */
	SET_BIT(SPI_u8_SPCR_REG,4);
	/* Clock Polatity Falling/Rising  Clock Phase Setup/Sample */
	SET_BIT(SPI_u8_SPCR_REG,3);
	SET_BIT(SPI_u8_SPCR_REG,2);
	#else
		#error "Wrong Choice"
	#endif

    /* Enable SPI */
	SET_BIT(SPI_u8_SPCR_REG,6);
	
}

u8   SPI_u8TransRecive(u8 Copy_u8DataByte ,u8 * Copy_pu8RecievedData)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_pu8RecievedData != NULL)
	{
		/* Send Data Byte */
		SPI_u8_SPDR_REG = Copy_u8DataByte;
		/* Check The Flag */
		while(!GET_BIT(SPI_u8_SPSR_REG,7));
		/* Read The Input Data */
		*Copy_pu8RecievedData = SPI_u8_SPDR_REG;
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;
}