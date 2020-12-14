#include "temperature.hpp"

double removeNan(double d, double e) {
    return isnan(d) ? d : e;
}
Temperature::Temperature() : themocouple0(CLK, CS0, DO),
                             themocouple1(CLK, CS1, DO) {
    themocouple0.begin();
    themocouple1.begin();
}

void Temperature::update() {
    // T1 = removeNan(themocouple0.readCelsius(), T1);
    // T2 = removeNan(themocouple1.readCelsius(), T2);
    T1 = themocouple0.readCelsius();
    T2 = themocouple1.readCelsius();
}
String Temperature::toString() {
    return String(T1) + String(T2);
}