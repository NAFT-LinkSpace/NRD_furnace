#include "temperature.hpp"

static double removeNan(double maynan, double e) {
    return isnan(maynan) ? e : maynan;
}
Temperature::Temperature()
    : themocouple0(CLK, CS0, DO),
      themocouple1(CLK, CS1, DO),
      themocouple2(CLK, CS2, DO) {
}
void Temperature::begin() {
    T0 = 0.0;
    T1 = 0.0;
    T2 = 0.0;

    // wait for MAX chip to stabilize
    delay(500);
    themocouple0.begin();
    themocouple1.begin();
    themocouple2.begin();
}

void Temperature::update() {
    // con.current_tempT0 = removeNan(themocouple0.readCelsius(), con.current_tempT0);
    // con.current_tempT1 = removeNan(themocouple1.readCelsius(), con.current_tempT1);
    // con.current_tempT2 = removeNan(themocouple2.readCelsius(), con.current_tempT2);

    T0 = removeNan(themocouple0.readCelsius(), T0);
    T1 = removeNan(themocouple1.readCelsius(), T1);
    T2 = removeNan(themocouple2.readCelsius(), T2);
    // T0 = themocouple0.readCelsius();
    // T1 = themocouple1.readCelsius();
    // T2 = themocouple2.readCelsius();
    if (millis() % 1000 == 0) {
        // Serial.print(themocouple0.readError());
        // Serial.print(themocouple1.readError());
        // Serial.print(themocouple2.readError());
        // Serial.println();
        Serial.println(toString());
    }
}
String Temperature::toString(const String delim) {
    return String(T0) + delim + String(T1) + delim + String(T2);
}