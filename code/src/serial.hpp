#ifndef SERIAL_COMMUNICATION_HEADER_FILE
#define SERIAL_COMMUNICATION_HEADER_FILE

#include <Arduino.h>

#include "container.hpp"
#include "keyword.hpp"

void setupSerial(const unsigned long baud = 19200);
void readSerial(Container& con);
void readSerialhelper(Container& con);

void writeSerial(const String str);
void rmCRLF(String& s);
double strTodError(const String);

int split(const String s, const int slen, String* dst, const int dstsize, const char delim = ',');
#endif