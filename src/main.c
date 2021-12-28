#include "main.h"
#include "InitDevice.h"
#include "tm1829.h"

volatile bit data_ready = 0; // nothing to send
volatile bit data_pwm; // if 1 then pwm data is sending
volatile uint8_t idata SPI_cur[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)
volatile uint8_t idata SPI_pwm[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
   PCA0MD &= ~PCA0MD_WDTE__ENABLED;    // Disable the watchdog timer;
}
 

//SI_INTERRUPT_PROTO(SPI0_ISR, SPI0_IRQn);
//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------
void main (void)
{
//   uint8_t test_value = 0x55;
//   uint8_t test_array[MAX_BUFFER_SIZE] = {1,2,3,4,5,6,7,8};
//   uint8_t i;
  //bit b = 0;

  initHW();
  GND = 0;

   //IE_EA = 1;                          // Enable global interrupts

  PCA0 = 0; // DEBUG reset counter
  sendCurrentRGB(3,2,1); // 0 - 31
                                       // finished
/*
   // Copy test_array into SPI_Data_Array
   for (i = 0; i < MAX_BUFFER_SIZE; i++)
   {
      SPI_Data_Array[i] = test_array[i];
   }

   // Send the array to the slave
   SPI_Array_Write ();

   while (!SPI0CN_NSSMD0);             // Wait until the Write transfer has
*/                                       // finished


   // END OF TEST -------------------------------------------------------------

   while (1)
   {

   }
}
