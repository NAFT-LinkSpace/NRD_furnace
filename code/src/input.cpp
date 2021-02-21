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

    temperature.update(con.common_.current_tempT0, con.common_.current_tempT1, con.common_.current_tempT2);
    return con;
}