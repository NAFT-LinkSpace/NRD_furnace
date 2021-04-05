#include <Arduino.h>
#include <Wire.h>

#include "container.hpp"
#include "convert.hpp"
#include "input.hpp"
#include "state.hpp"

void setup() {
    inputBegin();
}
// unsigned long pret = 0;
// unsigned long t = 0;

void loop() {
    // put your main code here, to run repeatedly:
    // t = millis();

    auto input_con = input();
    convert(input_con);
    // Serial.println();
    // if (t - pret < 0) {
    //     delay(20 - (t - pret));
    //     Serial.println(20 - (t - pret));
    // }
    // pret = t;
}
