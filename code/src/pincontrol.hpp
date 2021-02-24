#ifndef OUTPUT_HEADER_FILE
#define OUTPUT_HEADER_FILE

#include <Arduino.h>

#include "pin.hpp"

inline void pinControlBegin() {
    pinMode(PWMOUT, OUTPUT);
}

inline const double satirate(double d, const double uplim, const double dowmlim) {
    if (d > uplim) {
        return uplim;
    } else if (d < dowmlim) {
        return dowmlim;
    }
    return d;
}
inline void setPWM(const double duty_percent) {
    // int tmp = satirate(duty, 1, 0) * 255;
    int tmp = satirate(duty_percent, 100, 0) / 100 * 255;  //%

    // Serial.println("out");
    // Serial.println(tmp);
    analogWrite(PWMOUT, tmp);
}

inline void setLongPeriodPWM(const double duty_percent, const unsigned long period_ms, const unsigned long now_ms) {
    const double sati_duty = satirate(duty_percent, 100, 0);
    int nowv = (now_ms % period_ms) * 100 / period_ms;
    digitalWrite(PWMOUT, nowv < sati_duty);
    // Serial.println(nowv < duty_percent);
}
#endif