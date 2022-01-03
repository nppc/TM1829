#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <SI_C8051F530_Register_Enums.h>

#define SPIBITS 3

SI_SBIT(GND, SFR_P1, 5); // debug


extern bit buf0_full;  
extern bit buf1_full; 

extern uint8_t idata SPI_buf0[];
extern uint8_t idata SPI_buf1[];

extern uint16_t tmp_millis;
extern bit delay_on;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;

#endif /* SRC_MAIN_H_ */
