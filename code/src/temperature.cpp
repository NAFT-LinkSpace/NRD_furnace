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
    // wait for MAX chip to stabilize
    delay(500);
    themocouple0.begin();
    themocouple1.begin();
    themocouple2.begin();
}

void Temperature::update(double& T0, double& T1, double& T2) {
    T0 = removeNan(themocouple0.readCelsius(), T0);
    T1 = removeNan(themocouple1.readCelsius(), T1);
    T2 = removeNan(themocouple2.readCelsius(), T2);
}
// String Temperature::toString(const String delim) {
//     return String(T0) + delim + String(T1) + delim + String(T2);
// }