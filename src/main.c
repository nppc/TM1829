#include "main.h"
#include "InitDevice.h"
#include "tm1829.h"
#include "spi.h"

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
       for(i=0;i<20;i++){
         for(i1=0;i1<250;i1++){
             SPI_Byte_Write(0xFF); // hold line high
         }
       }


       for(i=0;i<7;i++){
           for(i1=0;i1<9;i1++){
               SPI_Byte_Write(SPI_cur[i1]); // hold line high
           }
       }

       for(i=0;i<20;i++){
         for(i1=0;i1<250;i1++){
             SPI_Byte_Write(0xFF); // hold line high
         }
       }

       for(i=0;i<3;i++){
           for(i1=0;i1<9;i1++){
               SPI_Byte_Write(SPI_pwm[i1]); // hold line high
           }
       }

   }
}
