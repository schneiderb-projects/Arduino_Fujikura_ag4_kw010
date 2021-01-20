#include "Fujikura_ag4_kw010.h"
#include <Arduino.h>
#include <Wire.h>

byte* values = new byte[2];

Fujikura_ag4_kw010::Fujikura_ag4_kw010(int sda, int scl) {
    Wire.begin(sda, scl);
}

byte* Fujikura_ag4_kw010::scan(byte* addresses)
{
  //Serial.println ();
  //Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

    for (byte i = 0; i < 127; i++)
  {
    Wire.beginTransmission (i);          // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response)
    {
      addresses[count++] = i;
    }
  }
  return addresses;
}

byte* Fujikura_ag4_kw010::read_registers(byte address, byte* values) {
  Wire.beginTransmission(address); // select device with "beginTransmission()"
  Wire.write(0); // select starting register with "write()"
  Wire.endTransmission(); // end write operation, as we just wanted to select the starting register
  Wire.requestFrom(address, 2); // select number of bytes to get from the device (2 bytes in this case)
  for (int i = 0; i < 2; i++) {
    if (Wire.available() >= 1) {
      values[i] = Wire.read();
    }
  }

  return values;
}


int Fujikura_ag4_kw010::parse_status(byte* values) {
  return ((0b11000000 & values[0]) >> 6);
}

uint16_t Fujikura_ag4_kw010::parse_pressure_data(byte* values) {
  return (values[0] & 0b00111111) << 8 | values[1];
}

double Fujikura_ag4_kw010::parse_pressure_kPa(byte* values) {
  return (parse_pressure_data(values) - 8192)/(7373.0/10.0);
}


double Fujikura_ag4_kw010::parse_pressure_mBar(byte* values) {
  return parse_pressure_kPa(values) * 10;
}


double Fujikura_ag4_kw010::read_pressure(int address) {
  //start the communication with IC with the address xx
  read_registers(address, values);
  
  int status_value = parse_status(values);
  if(status_value != 0) {return read_pressure(address);}
  double pressure = parse_pressure_mBar(values);
    
  return pressure;
}
