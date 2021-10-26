#include <EEPROM.h> 

void setup() {
  Serial.begin(9600);

}
int EEPROMReadInt(int address)
      {
      //Read the 4 bytes from the eeprom memory.
      int lowByte = EEPROM.read(address);
      int highByte = EEPROM.read(address + 1);


      //Return the recomposed int by using bitshift.
      return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
      }
      int valor = 0;
      int i = 0;
void loop() {
  
  valor = EEPROMReadInt(i);
  i++;
  i++;
  Serial.print("valor: ");
  Serial.print(valor);
  Serial.print("\n");
  Serial.print("i: ");
  Serial.print(i);
  Serial.print("\n");

}
