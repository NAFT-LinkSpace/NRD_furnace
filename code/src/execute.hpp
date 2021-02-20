#ifndef EXECUTE_HEADER_FILE
#define EXECUTE_HEADER_FILE

#include <Arduino.h>

#include "container.hpp"
#include "serial.hpp"

// typedef void (*Execute_func)(const Container& con);

// void execute_Default(const Container&);
// void execute_READ_TEMP(const Container& con);
// void execute_SET_TEMP(const Container& con);
// void execute_SET_DUTY(const Container& con);
// void execute_CONTROL(const Container& con);

// typedef struct {
//     String command;
//     Execute_func func;
// } FuncPair;

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