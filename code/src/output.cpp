#include "output.hpp"

// arduino uno
// duty :percent
void outputInit() {
    pinMode(PWMOUT, OUTPUT);
}
void setPwm(const int duty) {
    int tmp = int(satirate(double(duty), 100, 0) * 255 / 100);
    // Serial.println("out");
    // Serial.println(tmp);
    analogWrite(PWMOUT, tmp);
}
double satirate(double d, double uplim, double dowmlim) {
    if (d > uplim) {
        return uplim;
    } else if (d < dowmlim) {
        return dowmlim;
    }
    return d;
}
