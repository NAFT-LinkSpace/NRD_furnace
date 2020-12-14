#ifndef OUTPUT_HEADER_FILE
#define OUTPUT_HEADER_FILE

#include <Arduino.h>

#include "pin.hpp"
void outputInit();
void setPwm(const int duty);
double satirate(double d, double uplim, double dowmlim);

#endif