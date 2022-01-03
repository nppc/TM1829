//#pragma src
#include "main.h"
#include "spi.h"

// bit addressible variable
bdata unsigned char btmp;
sbit btmp0 = btmp^0;
sbit btmp1 = btmp^1;
sbit btmp2 = btmp^2;
sbit btmp3 = btmp^3;
sbit btmp4 = btmp^4;
sbit btmp5 = btmp^5;
sbit btmp6 = btmp^6;
sbit btmp7 = btmp^7;

// 3bits of SPI for 1bit OneWireLED
// SPI_Byte_Write (0x03); //send 0 (0b011)
// SPI_Byte_Write (0x01); //send 1 (0b001)
// 176 MCU cycles
void sendCurrentRGB(uint8_t r, uint8_t g, uint8_t b, bit test){
  uint8_t data *adr;
  bit buff; // idicate selected buffer

  // inverse it as we will use the bit as it is, but it need to be used inversed as middle bit is inversed (0 = 011, 1=001)
  r=~r;
  g=~g;
  b=~b;

  while(buf0_full & buf1_full); // wait if both buffers are full
  if(buf0_full){
	adr = SPI_buf1;
	buff = 1;
  } else {
	adr = SPI_buf0;
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
  btmp = 0x24; btmp6 = (r & 0x10); btmp3 = (r & 0x08); btmp0 = (r & 0x04);
  *adr = btmp;
  adr++;
  btmp = 0x92; btmp5 = (r & 0x02); btmp2 = (r & 0x01);
  *adr = btmp;
  adr++;
  btmp = 0x49; btmp7 = (g & 0x10); btmp4 = (g & 0x08); btmp1 = (g & 0x04);
  *adr = btmp;
  adr++;
  btmp = 0x24; btmp6 = (g & 0x02); btmp3 = (g & 0x01); btmp0 = (b & 0x10);
  *adr = btmp;
  adr++;
  btmp = 0x92; btmp5 = (b & 0x08); btmp2 = (b & 0x04);
  *adr = btmp;
  adr++;
  btmp = (test ? 0x49 : 0x4B); btmp7 = (b & 0x02); btmp4 = (b & 0x01);
  *adr = btmp;

  if(buff) buf1_full = true; else buf0_full = true; // data is ready for sending
}

// 3bits of SPI for 1bit OneWireLED
// SPI_Byte_Write (0x03); //send 0 (0b011)
// SPI_Byte_Write (0x01); //send 1 (0b001)
// 218 MCU cycles
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
	adr = SPI_buf1;
	buff = 1;
  } else {
	adr = SPI_buf0;
	buff = 0;
  }

  // first - prepare an array for sending
  // 24 bits. 0xFF - means CURRENT
  // 8X3 bits. - RGB
  // SPI bits (9): 0R1 0R1 0R|1 0R1 0R1 0|R1 0R1 0R1| 0G1 0G1 0G|1 0G1 0G1 0|G1 0G1 0G1| 0B1 0B1 0B|1 0B1 0B1 0|B1 0B1 0B1
  btmp = 0x24; btmp6 = (r & 0x80); btmp3 = (r & 0x40); btmp0 = (r & 0x20);
  *adr = btmp;
  adr++;
  btmp = 0x92; btmp5 = (r & 0x10); btmp2 = (r & 0x08);
  *adr = btmp;
  adr++;
  btmp = 0x49; btmp7 = (r & 0x04); btmp4 = (r & 0x02); btmp1 = (r & 0x01);
  *adr = btmp;
  adr++;

  btmp = 0x24; btmp6 = (g & 0x80); btmp3 = (g & 0x40); btmp0 = (g & 0x20);
  *adr = btmp;
  adr++;
  btmp = 0x92; btmp5 = (g & 0x10); btmp2 = (g & 0x08);
  *adr = btmp;
  adr++;
  btmp = 0x49; btmp7 = (g & 0x04); btmp4 = (g & 0x02); btmp1 = (g & 0x01);
  *adr = btmp;
  adr++;

  btmp = 0x24; btmp6 = (b & 0x80); btmp3 = (b & 0x40); btmp0 = (b & 0x20);
  *adr = btmp;
  adr++;
  btmp = 0x92; btmp5 = (b & 0x10); btmp2 = (b & 0x08);
  *adr = btmp;
  adr++;
  btmp = 0x49; btmp7 = (b & 0x04); btmp4 = (b & 0x02); btmp1 = (b & 0x01);
  *adr = btmp;

  if(buff) buf1_full = true; else buf0_full = true; // data is ready for sending
}

