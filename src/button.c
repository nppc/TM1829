//#pragma src
// Button routines
#include "button.h"
#include "tm1829.h"
#include "gen.h"

volatile uint16_t buttonTmr;
volatile bool buttonLastState;

// use some big timer number for the counter base after debounce (let's say 1000) to prevent repeting of the action.
// if button is pressed and last state of button is different, start a timer for 40ms (debounce)
// if button is released then set last state of button to 0 (timer will stop)
// if after debounce time button still pressed, do action but continue to run timer

void processButtons(void){
  bool butPwr;
  uint16_t tmpTmr;
  // 1 - pressed, 0 - not pressed
  butPwr = !PIN_BUT;
  // if button is pressed
  if(butPwr){
    // read timer only if button is pressed. Otherwise we not interested in timer
    IE_EA = 0;
    tmpTmr = buttonTmr; // the variable buttonTmr is updated in interrupt
    IE_EA = 1;
  }else{
    // if no buttons pressed, then just exit
    buttonLastState = 0; // stop the timer
    return;
  }
  if(butPwr && !buttonLastState){
    // button is just pressed, start the timer
    IE_EA = 0;
    buttonTmr = 0; // the variable buttonTmr is updated in interrupt
    IE_EA = 1;
  }
  buttonLastState = 1; // update button last state

  // check for debounce
  if(tmpTmr<BUTTON_DEBOUNCE){
    return; // exit as we not yet debounced
  }
  // are we ready to run the action for the first time after debounce?
  if(tmpTmr>=BUTTON_DEBOUNCE && tmpTmr<1000){
    // run the action again
    buttonAction(butPwr);
    // base the timer above debounce mark
    IE_EA = 0;
    buttonTmr = 1000; // the variable buttonTmr is updated in interrupt
    IE_EA = 1;
    return;
  }

}

void buttonAction(bool butPwr){
  if(butPwr){
    if(fader.state == FADE_OUT || fader.cntr_step == 0){
        fader.state = FADE_IN;
        //delay_ms(5);
        //sendCurrentRGB(CURRENT_B,CURRENT_R,CURRENT_G, false); // 0 - 31
    }else{
        fader.state = FADE_OUT;
    }
	delay_ms(5); // interrupt all remaining LEDs updates and start over
	fader.cntr_led = 0;
  }

}
