//#pragma src
#include "main.h"

SI_INTERRUPT(SPI0_ISR, SPI0_IRQn)
{
  static uint8_t buf_i = 0; // index in the buffer
  static bit cur_buf = 0; // current buffer that is processing by SPI0 Interrupt
  static uint8_t data *bufadr; // address for current buffer
  if(buf0_full | buf1_full){
    if(buf_i==0){
		if(buf0_full & cur_buf){ // set buffer 0 if buffer 0 is full and last was buffer 1
			*bufadr = SPI_buf0;
			cur_buf = 0;
		}else if(buf1_full & !cur_buf){ // set buffer 1 if buffer 1 is full and last was buffer 0
			*bufadr = SPI_buf1;
			cur_buf = 1;
		}else{ // if we need to work with not expected buffer, then nothing to do, we need to read the buffer provided
			if(buf0_full){
				*bufadr = SPI_buf0;
				cur_buf = 0;
			}else{
				*bufadr = SPI_buf1;
				cur_buf = 1;
			}
		}
	}
	// send data from buffer indicated by cur_buf
	SPI0DAT = bufadr[buf_i];
	buf_i++;
	// should we finish sending buffer?
	if(buf_i>=sizeof(SPI_buf0)){
		buf_i = 0; // reset buffer index
		if(cur_buf) buf1_full = false; else buf0_full = false; // indicate that buffer is empty
	}
  }else{
    // nothing to send
	SPI0DAT = 0xFF; // hold line high
	cur_buf = 0; // if nothing to send, then next time start processing from buf0.
  }
  SPI0CN_SPIF = 0; // Clear the SPIF flag

}

