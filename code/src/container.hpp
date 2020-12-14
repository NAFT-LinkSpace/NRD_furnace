#ifndef CONTAINER_HEAEDER_FILE
#define CONTAINER_HEAEDER_FILE

#include <Arduino.h>

class Container {
   public:
    String command;
    double target_temp;  //[℃]
    double duty;         //percent

    double current_tempT1;  //[℃]
    double current_tempT2;  //[℃]

    String toString();
};

#endif