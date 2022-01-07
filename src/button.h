
#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

SI_SBIT(PIN_GND, SFR_P1, 5); // button gnd
SI_SBIT(PIN_BUT, SFR_P1, 6); // button pin

// values in ms
#define BUTTON_DEBOUNCE 40

extern void processButtons(void);
extern void buttonAction(bool butPwr);

extern uint16_t buttonTmr;
extern bool buttonLastState;

#endif /* BUTTON_H_ */
