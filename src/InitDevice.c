#include "main.h"
#include "InitDevice.h"

void initHW(void){
  // PCA for debug purposes
  PCA0CN    = 0x40;
  PCA0MD    &= ~0x40;
  PCA0MD    = 0x08;
  PCA0CPM2  = 0x48;

  // Set internal oscillator to run at its maximum frequency
   OSCICN = OSCICN_IOSCEN__ENABLED |
            OSCICN_IFCN__HFOSC_DIV_1;

   // Port init
   P1MDOUT   = P1MDOUT_B4__PUSH_PULL | P1MDOUT_B5__PUSH_PULL; // debug on 1.5
   P0SKIP    = 0xFF;
   P1SKIP    = 0x03;
   XBR0 = XBR0_SPI0E__ENABLED;  // Enable the SPI on the XBAR
   XBR1 = XBR1_XBARE__ENABLED;  // Enable crossbar

   //SPI0
   //SPI0CKR   = 0x01; // 6125Khz (8 * 765Khz) - closest to 800Khz
#if SPIBITS == 3
   SPI0CKR   = 0x04; // 2450Khz (3 * 816Khz) - closest to 800Khz
#else
   SPI0CKR   = 0x01; // 6125Khz (8 * 765Khz) - closest to 800Khz
#endif
   SPI0CFG   = SPI0CFG_MSTEN__MASTER_ENABLED;  // Enable the SPI as a Master
   SPI0CN    = SPI0CN_SPIEN__ENABLED;  // 3-wire Single Master, SPI enabled
   IE_ESPI0  = 1;  // Enable SPI interrupts

}
