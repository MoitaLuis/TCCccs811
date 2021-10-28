#include "Adafruit_CCS811.h"
#include <EEPROM.h>

Adafruit_CCS811 ccs;
boolean danger = false;
int addr = 0;
void setup() {
  Serial.begin(9600);

  Serial.println("CCS811 test");
  pinMode(10, OUTPUT);
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  //Modo de operação:
  ccs.setDriveMode(CCS811_DRIVE_MODE_60SEC);
  // Wait for the sensor to be ready
  while(!ccs.available());
}

//salva o valor de co2 na memória permanente
void writeIntIntoEEPROM(int address, int number){ 
  byte lowByte  = ((number >> 0) & 0xFF);;
  byte highByte  = ((number >> 8) & 0xFF);

  EEPROM.write(address, lowByte);
  EEPROM.write(address + 1, highByte);
}
      
void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      
      //imprime o valor de co2 no serial
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());

      

      writeIntIntoEEPROM(addr, ccs.geteCO2());
      
      
      // avança o endereço de memória para salvar os dados em sequência
      addr = addr + 2;
      
      // se addr for ultrapassar o tamanho da memória --> volta para o início da memória
      if (addr == EEPROM.length()) {
          addr = 0;
      }

      // alerta sonoro
      if(ccs.geteCO2() > 1000 && danger == false){
         digitalWrite(10, HIGH);
         delay(500);
         digitalWrite(10, LOW);
         delay(500);
         digitalWrite(10, HIGH);
         delay(500);
         digitalWrite(10, LOW);
         delay(500);
         digitalWrite(10, HIGH);
         delay(800);
         digitalWrite(10, LOW);
         danger = true;
         
      }
      
      // acende LED vermelho, apaga LED verde
      if(danger){
          digitalWrite(8, LOW);
          digitalWrite(9,HIGH);          
      }

      // comparação com limiar inferior para alterar estado de perigo
      if(ccs.geteCO2() < 900 && danger == true){
        danger = false;
      }

      // Acende LED verde em situação normal
      if(ccs.geteCO2() < 1000 && danger == false){
        digitalWrite(10, LOW); 
        digitalWrite(9, LOW); 
        digitalWrite(8,HIGH);
      }
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(500);
}
