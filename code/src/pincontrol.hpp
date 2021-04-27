#ifndef OUTPUT_HEADER_FILE
#define OUTPUT_HEADER_FILE

#include <Arduino.h>

#include "pin.hpp"
#include "queue.hpp"

inline void pinControlBegin() {
    pinMode(PWMOUT, OUTPUT);
}

inline void setPWM(const double duty_percent) {
    const double sati_duty = constrain(duty_percent, 0, 100);
    normal_queue.push(toStringHelper("duty[%]", sati_duty));

    int tmp = sati_duty / 100 * 255;  //%
    analogWrite(PWMOUT, tmp);
}

inline void setLongPeriodPWM(const double duty_percent, const unsigned long period_ms, const unsigned long now_ms) {
    const double sati_duty = constrain(duty_percent, 0, 100);
    normal_queue.push(toStringHelper("duty[%]", sati_duty));

    int nowv = (now_ms % period_ms) * 100 / period_ms;
    digitalWrite(PWMOUT, nowv < sati_duty);
}
#endif