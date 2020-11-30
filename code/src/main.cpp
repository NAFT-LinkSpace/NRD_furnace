#include <Arduino.h>
#include <Wire.h>

#include "pin.hpp"
#include "temperature.hpp"

Temperature temperature;
void setup() {
    // put your setup code here, to run once:
    pinMode(PWMOUT, OUTPUT);
    temperature.init();
}

void loop() {
    // put your main code here, to run repeatedly:
    temperature.update();
}