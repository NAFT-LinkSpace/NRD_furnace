#ifndef SERIAL_COMMUNICATION_HEADER_FILE
#define SERIAL_COMMUNICATION_HEADER_FILE

#include <Arduino.h>

#include "keyword.hpp"

void setupSerial(const unsigned long baud = 19200);
String readSerial();
// void readSerialhelper();

// void writeSerial(const String str);
void rmCRLF(String& s);


#endif