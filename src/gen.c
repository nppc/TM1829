#include "main.h"

void delay_ms(uint16_t ms_count)
 {
  tmp_millis = ms_count;
  delay_on = 1;
  while(delay_on);
 }
