//#pragma src
#include "main.h"
#include "spi.h"

#if SPIBITS == 3
// 3bit SPI for 1bit OneWireLED
// SPI_Byte_Write (0x03); //send 0 (0b011)
// SPI_Byte_Write (0x01); //send 1 (0b001)
// 198 MCU cycles
void sendCurrentRGB(uint8_t r, uint8_t g, uint8_t b){
  uint8_t data *adr;
  bit buff; // idicate selected buffer

  // inverse it as we will use the bit as it is, but it need to be used inversed as middle bit is inversed (0 = 011, 1=001)
  r=~r;
  g=~g;
  b=~b;

  while(buf0_full & buf1_full); // wait if both buffers are full
  if(buf0_full){
	*adr = SPI_buf1;
	buff = 1;
  } else {
	*adr = SPI_buf0;
	buff = 0;
  }
  
  // first - prepare an array for sending
  // First byte = 0xFF - means CURRENT
  // SPI bits: 001 001 00|1 001 001 0|01 001 001 (0x24, 0x92, 0x49)
  *adr = 0x24;
  adr++;
  *adr = 0x92;
  adr++;
  *adr = 0x49;
  adr++;

  // 5X3 bits. - RGB current + T bit (0 - it is not a test)
  // SPI bits: 0R1 0R1 0R|1 0R1 0R1 0|G1 0G1 0G1| 0G1 0G1 0B|1 0B1 0B1 0|B1 0B1 011
  *adr = ((r & 0x10)<<2) | (r & 0x08) | ((r & 0x04)>>2) | 0x24;
  adr++;
  *adr = ((r & 0x02)<<4) | ((r & 0x01)<<2) | 0x92;
  adr++;
  *adr = ((g & 0x10)<<3) | ((g & 0x08)<<1) | ((g & 0x04)>>1) | 0x49;
  adr++;
  *adr = ((g & 0x02)<<5) | ((g & 0x01)<<3) | ((b & 0x10)>>4) | 0x24;
  adr++;
  *adr = ((b & 0x08)<<2) | (b & 0x04) | 0x92;
  adr++;
  *adr = ((b & 0x02)<<6) | ((b & 0x01)<<4) | 0x4B;

  if(buff) buf1_full = true; else buf0_full = true; // data is ready for sending
}

// 3bit SPI for 1bit OneWireLED
// SPI_Byte_Write (0x03); //send 0 (0b011)
// SPI_Byte_Write (0x01); //send 1 (0b001)
// 297 MCU cycles
void sendPwmRGB(uint8_t r, uint8_t g, uint8_t b){
  uint8_t data *adr;
  bit buff; // idicate selected buffer

  // inverse it as we will use the bit as it is, but it need to be used inversed as middle bit is inversed (0 = 011, 1=001)
  if(r==255) r=254;  // remove last bit just in case as first byte cannot be all 1s
  r=~r;
  g=~g;
  b=~b;

  while(buf0_full & buf1_full); // wait if both buffers are full
  if(buf0_full){
	*adr = SPI_buf1;
	buff = 1;
  } else {
	*adr = SPI_buf0;
	buff = 0;
  }

  // first - prepare an array for sending
  // 24 bits. 0xFF - means CURRENT
  // 8X3 bits. - RGB
  // SPI bits (9): 0R1 0R1 0R|1 0R1 0R1 0|R1 0R1 0R1| 0G1 0G1 0G|1 0G1 0G1 0|G1 0G1 0G1| 0B1 0B1 0B|1 0B1 0B1 0|B1 0B1 0B1
  *adr = ((r & 0x80)>>1) | ((r & 0x40)>>3) | ((r & 0x20)>>5) | 0x24;
  adr++;
  *adr = ((r & 0x10)<<1) | ((r & 0x08)>>1) | 0x92;
  adr++;
  *adr = ((r & 0x04)<<5) | ((r & 0x02)<<3) | ((r & 0x01)<<1) | 0x49;
  adr++;

  *adr = ((g & 0x80)>>1) | ((g & 0x40)>>3) | ((g & 0x20)>>5) | 0x24;
  adr++;
  *adr = ((g & 0x10)<<1) | ((g & 0x08)>>1) | 0x92;
  adr++;
  *adr = ((g & 0x04)<<5) | ((g & 0x02)<<3) | ((g & 0x01)<<1) | 0x49;
  adr++;

  *adr = ((b & 0x80)>>1) | ((b & 0x40)>>3) | ((b & 0x20)>>5) | 0x24;
  adr++;
  *adr = ((b & 0x10)<<1) | ((b & 0x08)>>1) | 0x92;
  adr++;
  *adr = ((b & 0x04)<<5) | ((b & 0x02)<<3) | ((b & 0x01)<<1) | 0x49;

  if(buff) buf1_full = true; else buf0_full = true; // data is ready for sending
}

#endif

#if SPIBITS == 8
// 8bit SPI for 1bit OneWireLED
// SPI_Byte_Write (0x3F); //send 0 (0b00111111)
// SPI_Byte_Write (0x07); //send 1 (0b00000111)
// 504 MCU cycles
void sendCurrentRGB(uint8_t r, uint8_t g, uint8_t b){
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
  data_ready = true; // send data


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
