#include "Fujikura_ag4_kw010.h"

Fujikura_ag4_kw010 f(23,22); //int sda, int scl

void setup() { 
  Serial.begin(115200);
}

void loop() {
  byte* address = new byte[1]; //create array for address to be written too
  f.scan(address); //scan for i2c devices and write the address of any devices found into the address array
  Serial.println(f.read_pressure(address[0])); //read the pressure in mBar from the pressure sensor whos address was stored at address[0]
  delay(100);
}
