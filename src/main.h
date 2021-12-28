#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <SI_C8051F530_Register_Enums.h>

#define SPIBITS 3

SI_SBIT(GND, SFR_P1, 5); // debug


extern bit data_ready; // data on SPI0
extern bit data_pwm; // what to send pwm or current

extern uint8_t idata SPI_cur[];
extern uint8_t idata SPI_pwm[];


#endif /* SRC_MAIN_H_ */
