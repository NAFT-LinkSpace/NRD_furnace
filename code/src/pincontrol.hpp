#ifndef OUTPUT_HEADER_FILE
#define OUTPUT_HEADER_FILE

#include <Arduino.h>

#include "pin.hpp"
void pinControlBegin();
void setPWM(const double duty);
void setLongPeriodPWM(const double duty_percent, const unsigned long period_ms, const unsigned long now_ms);

const double satirate(double d, const double uplim, const double dowmlim);

#endif