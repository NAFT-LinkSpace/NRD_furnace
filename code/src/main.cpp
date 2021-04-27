#include <Arduino.h>
#include <Wire.h>

#include "container.hpp"
#include "convert.hpp"
#include "input.hpp"
#include "state.hpp"

void setup() {
    inputBegin();
}

void loop() {
    // put your main code here, to run repeatedly:

    convert(input());
}
