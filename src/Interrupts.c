//#pragma src
#include "main.h"

SI_INTERRUPT(SPI0_ISR, SPI0_IRQn)
{
   //static uint8_t array_index = 0;
  if(data_ready){

  }else{
      SPI0DAT = 0xFF; // hold line high
  }
  SPI0CN_SPIF = 0; // Clear the SPIF flag

}

