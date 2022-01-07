#include "main.h"
#include "InitDevice.h"
#include "tm1829.h"
#include "spi.h"
#include "gen.h"
#include "button.h"

volatile bit buf0_full = 0; // nothing to send
volatile bit buf1_full = 0; // nothing to send

volatile uint8_t idata SPI_buf0[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)
volatile uint8_t idata SPI_buf1[3 * SPIBITS]; // N bytes to send via SPI (3 bytes of OneWire data)

volatile uint16_t tmp_millis;
volatile bit delay_on = false;

//volatile bit fadetick;
volatile fader_t fader;
volatile uint8_t fade_ms_cntr = 0;


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
  
  fader.cntr_step = 0;
  fader.cntr_led = 0;
  fader.state = FADE_OUT;

  initHW();
  PIN_GND = 0;

  IE_EA = 1; // Enable global interrupts
  SPI_Byte_Write(0xFF); // start SPI0 flow
  SPI_Byte_Write(0xFF); // and prefill the buffer

  delay_ms(50);

  for(i=0;i<LEDS_TOTAL;i++){
	sendCurrentRGB(CURRENT_B,CURRENT_R,CURRENT_G, false); // 0 - 31
  }
  delay_ms(5);

   while (1)
   {
		processButtons();
		fade();
   }
}
