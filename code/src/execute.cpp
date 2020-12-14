#include "execute.hpp"

void execute_Default(Container con) {
    return;
}

void execute_READ_TEMP(Container con) {
    // writeSerial("read_temp");
    writeSerial(con.toString());
}
void execute_SET_TEMP(Container con) {
}
void execute_SET_DUTY(Container con) {
    // writeSerial("set_duty");
    setPwm(con.duty);
}

// Strategy::Strategy() {
//     init();
// }
// Strategy::Strategy(Execute_func e) {
//     init();
//     execute_f = e;
// }
// void Strategy::init() {
//     con = {};
//     execute_f = execute_Default;
// }
// void Strategy::excute() {
//     execute_f(con);
// }
// void Strategy::setter(container::Container c, Execute_func e) {
//     con = c;
//     execute_f = e;
// }
