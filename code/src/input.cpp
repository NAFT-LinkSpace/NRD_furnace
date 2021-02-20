#include "input.hpp"

static Temperature temperature;
static InputContainer con;

void inputBegin() {
    setupSerial(19200);
    temperature.begin();
}
const InputContainer& input() {
    con.common_.now_ms = millis();
    con.message = readSerial();

    temperature.update();
    con.common_.current_tempT0 = temperature.T0;
    con.common_.current_tempT1 = temperature.T1;
    con.common_.current_tempT2 = temperature.T2;
    return con;
}