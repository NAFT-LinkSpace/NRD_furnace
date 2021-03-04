#ifndef OUTPUT_HEADER_FILE
#define OUTPUT_HEADER_FILE

#include <Arduino.h>

#include "pin.hpp"

inline void pinControlBegin() {
    pinMode(PWMOUT, OUTPUT);
}

inline void setPWM(const double duty_percent) {
    // int tmp = constrain(duty, 1, 0) * 255;
    int tmp = constrain(duty_percent, 0, 100) / 100 * 255;  //%

    analogWrite(PWMOUT, tmp);
}

inline void setLongPeriodPWM(const double duty_percent, const unsigned long period_ms, const unsigned long now_ms) {
    const double sati_duty = constrain(duty_percent, 0, 100);
    int nowv = (now_ms % period_ms) * 100 / period_ms;
    digitalWrite(PWMOUT, nowv < sati_duty);
}
#endif