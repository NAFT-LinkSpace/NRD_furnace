#ifndef EXECUTE_HEADER_FILE
#define EXECUTE_HEADER_FILE

#include <Arduino.h>

#include "container.hpp"
#include "output.hpp"
#include "serial.hpp"

typedef void (*Execute_func)(Container con);

void execute_Default(Container);
void execute_READ_TEMP(Container con);
void execute_SET_TEMP(Container con);
void execute_SET_DUTY(Container con);

// template <class C1, class C2>
// class Pair {
//    public:
//     C1 v1;
//     C2 v2;
// };
typedef struct {
    String command;
    Execute_func func;
} FuncPair;
// class Strategy {
//    public:
//     // Tuple<String, String> commandfuncpair;
//     container::Container con;
//     Execute_func execute_f;

//     Strategy();
//     Strategy(Execute_func);
//     void init();
//     void excute();
//     void setter(container::Container, Execute_func);
// };

#endif