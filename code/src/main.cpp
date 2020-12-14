#include <Arduino.h>
#include <Wire.h>

#include "container.hpp"
#include "execute.hpp"
#include "keyword.hpp"
#include "output.hpp"
#include "pin.hpp"
#include "serial.hpp"
#include "temperature.hpp"

Temperature temperature;
Container con;

FuncPair commandfuncpair[] = {
    {keyword::READ_TEMP, execute_READ_TEMP},
    {keyword::SET_DUTY, execute_SET_DUTY},
    {keyword::SET_TEMP, execute_SET_TEMP}};

void setup() {
    outputInit();

    setupSerial(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:

    readSerial(con);

    temperature.update();
    con.current_tempT1 = temperature.T1;
    con.current_tempT2 = temperature.T2;
    Serial.println(con.toString());
    for (auto &&tup : commandfuncpair) {
        if (tup.command == con.command) {
            tup.func(con);
        }
    }

    delay(1000);
}
