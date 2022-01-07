#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <SI_C8051F530_Register_Enums.h>

#define SPIBITS 3

#define LEDS_TOTAL 7
#define  COLOR_R  255
#define  COLOR_G  200
#define  COLOR_B  50
#define  CURRENT_R  31
#define  CURRENT_G  1
#define  CURRENT_B  10
#define FADE_DELAY 5

extern bit buf0_full;  
extern bit buf1_full; 

extern uint8_t idata SPI_buf0[];
extern uint8_t idata SPI_buf1[];

typedef enum {FADE_OUT, FADE_IN} fader_e;
typedef struct {
  //float r;
  //float g;
  //float b;
  uint8_t cntr_step; // current fade step (0-255)
  uint8_t cntr_led; // current led (0-6)
  fader_e state; // should we change light?
} fader_t;

//extern bit fadetick;
extern fader_t fader;
extern uint8_t fade_ms_cntr;

extern uint16_t tmp_millis;
extern bit delay_on;

/*
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;
*/
#endif /* SRC_MAIN_H_ */
