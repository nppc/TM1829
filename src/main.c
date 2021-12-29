#include "main.h"
#include "InitDevice.h"
#include "tm1829.h"
#include "spi.h"

volatile bit buf0_full = 0; // nothing to send
volatile bit buf1_full = 0; // nothing to send

volatile uint8_t idata SPI_buf0[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)
volatile uint8_t idata SPI_buf1[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)

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
 

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------
void main (void)
{
   uint8_t i;
   uint8_t i1;

  initHW();
  GND = 0;

   //IE_EA = 1; // Enable global interrupts

  //PCA0 = 0; // DEBUG reset counter
  sendCurrentRGB(0,0,0); // 0 - 31
  sendPwmRGB(255,255,255); // 0 = 255

   while (1)
   {
		
   }
}
