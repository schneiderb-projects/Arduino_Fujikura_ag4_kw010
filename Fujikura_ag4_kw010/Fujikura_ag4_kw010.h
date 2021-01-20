#ifndef Fujikura_ag4_kw010_h
#define Fujikura_ag4_kw010_h

#include "Arduino.h"

class Fujikura_ag4_kw010
{
    public: 
        Fujikura_ag4_kw010(int sda, int scl);
        byte* read_registers(byte address, byte* values);
        int parse_status(byte* values);
        uint16_t parse_pressure_data(byte* values);
        double parse_pressure_kPa(byte* values);
        double parse_pressure_mBar(byte* values);
        double read_pressure(int address);
        byte* scan(byte* addresses);
};

#endif 
