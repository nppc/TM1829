#include "main.h"
#include "InitDevice.h"
#include "tm1829.h"
#include "spi.h"
#include "gen.h"

volatile bit buf0_full = 0; // nothing to send
volatile bit buf1_full = 0; // nothing to send

volatile uint8_t idata SPI_buf0[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)
volatile uint8_t idata SPI_buf1[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)

volatile uint16_t tmp_millis;
volatile bit delay_on = 0;


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
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t rc = 0;
  uint8_t gc = 0;
  uint8_t bc = 0;
  bit test = true;

  initHW();
  GND = 0;

  IE_EA = 1; // Enable global interrupts

  SPI_Byte_Write(0x00); // start interrupts

  delay_ms(100);

   while (1)
   {
       delay_ms(10);
       sendCurrentRGB(bc,rc,gc, test); // 0 - 31
       sendCurrentRGB(0,0,0, true); // 0 - 31
       sendCurrentRGB(bc,rc,gc, test); // 0 - 31
       delay_ms(10);
       sendPwmRGB(b,r,g); // 0 = 255
       sendPwmRGB(b,r,g); // 0 = 255
       sendPwmRGB(b,r,g); // 0 = 255
       delay_ms(100);
   }
}
