#include "main.h"
#include "button.h"

volatile bit delay_tick;

void delay_ms(uint16_t ms_count)
 {
  uint16_t i;
  delay_tick = 0;
  for(i=0; i<ms_count;i++){
      while(!delay_tick);
      delay_tick = 0;
  }
 }

void timer_routines(void){
  if(timer1ms_tick){
      timer1ms_tick = false;

      // button routines
      if(buttonLastState) buttonTmr++;

      // fade rgb
      if(fade_ms_cntr != 0) fade_ms_cntr--;
  }
}
