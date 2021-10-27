#include <EEPROM.h>
int addr = 0;
void setup() {
  
}

void writeIntIntoEEPROM(int address, int number){ 
  byte lowByte  = ((number >> 0) & 0xFF);;
  byte highByte  = ((number >> 8) & 0xFF);

  EEPROM.write(address, lowByte);
  EEPROM.write(address + 1, highByte);
}


void loop() {
      writeIntIntoEEPROM(addr, 0);
      addr ++;

}
