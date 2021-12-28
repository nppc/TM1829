//#pragma src
#include "main.h"
#include "spi.h"

#if SPIBITS == 3
// 3bit SPI for 1bit OneWireLED
// SPI_Byte_Write (0x03); //send 0 (0b011)
// SPI_Byte_Write (0x01); //send 1 (0b001)
// ??? MCU cycles
void sendCurrentRGB(uint8_t r, g, b){
  uint8_t tmp;
  while(data_ready); // wait for all data to be sent
  // first - prepare an array for sending
  // 8 bits. 0xFF - means CURRENT
  // SPI bits: 001 001 00|1 001 001 0|01 001 001 (0x24, 0x92, 0x49)
  SPI_cur[0] = 0x24;
  SPI_cur[1] = 0x92;
  SPI_cur[2] = 0x49;
  // 5X3 bits. - RGB current + T bit (0)
  // SPI bits: 0R1 0R1 0R|1 0R1 0R1 0|G1 0G1 0G1| 0G1 0G1 0B|1 0B1 0B1 0|B1 0B1 011
  tmp = ((r & 0x10)<<2) | (r & 0x08) | ((r & 0x04)>>2) | 0x24;
  SPI_cur[3] = tmp;
  tmp = ((r & 0x02)<<4) | ((r & 0x01)<<2) | 0x92;
  SPI_cur[4] = tmp;
  // TODO: tmp = ((r & 0x02)<<4) | ((r & 0x01)<<2) | 0x92;
  SPI_cur[5] = tmp;
  data_ready = 1; // send data
}
#endif

#if SPIBITS == 8
// 8bit SPI for 1bit OneWireLED
// SPI_Byte_Write (0x3F); //send 0 (0b00111111)
// SPI_Byte_Write (0x07); //send 1 (0b00000111)
// 541 MCU cycles
void sendCurrentRGB(uint8_t r, g, b){
  uint8_t i, mask;
  while(data_ready); // wait for all data to be sent
  // first - prepare an array for sending
  // 8 bits. 0xFF - means CURRENT
  for(i=0;i<8;i++){
      SPI_cur[i] = 0x3F;
  }
  // 5 bits. - RED current
  mask = 0x10; // 0b00010000
  for(i=0;i<5;i++){
      SPI_cur[8+i] = ((r & mask) == 0 ? 0x3F : 0x07);
      SPI_cur[8+i+5] = ((g & mask) == 0 ? 0x3F : 0x07);
      SPI_cur[8+i+10] = ((b & mask) == 0 ? 0x3F : 0x07);
      mask = mask >> 1;
  }
  SPI_cur[23] = 0x07; // it is not test
  data_ready = 1; // send data


  // we assume that line is high
//  IE_EA = 0; // disable interrupts
//  data_sending = 1; // we initiating a data send
//  // send first data
//  IE_EA = 1; // enable interrupts
}
#endif

/*
void oneWire_sendByte(uint8_t bt){
  uint8_t i;
  for(i=0;i<8;i++){

  }

}
*/
