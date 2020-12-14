#include "container.hpp"
String Container::toString() {
    return command + "target_temp:" + String(target_temp) +
           "duty:" + String(duty) +
           "current temp T1:" + String(current_tempT1) +
           "T2:" + String(current_tempT2);
}