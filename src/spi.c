#include "main.h"
#include "spi.h"

void SPI_Byte_Write (uint8_t dat)
{
   while (!SPI0CN_TXBMT); // Wait until the SPI buffer is free, in case
   SPI0DAT = dat;
}

