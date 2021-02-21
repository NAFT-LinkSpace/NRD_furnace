#ifndef CONTAINER_HEAEDER_FILE
#define CONTAINER_HEAEDER_FILE

#include <Arduino.h>

#include "Stringer.hpp"
#include "parse.hpp"
// template <typename T>
// String toStringHelper(const String s, const T t);

struct CommonContainer {
    unsigned long now_ms;
    double current_tempT0;  //[℃]
    double current_tempT1;  //[℃]
    double current_tempT2;  //[℃]

    const String toString() const {
        return toStringHelper("now_ms", now_ms) +
               toStringHelper("current temp T0", current_tempT0) +
               toStringHelper("T1", current_tempT1) +
               toStringHelper("T2", current_tempT2);
    }

    void init() {
        now_ms = 0;
        current_tempT0 = 0.0;
        current_tempT1 = 0.0;
        current_tempT2 = 0.0;
    }
};
struct InputContainer {
   public:
    // String command;
    String message;

    unsigned int bottun_count;
    CommonContainer common_;

    const String toString() const {
        return toStringHelper("message", message) +
               toStringHelper("button count", bottun_count);
    }
    void init() {
        message = "";
        bottun_count = 0;
    }
};

class OutputContainer {
   public:
    // InputContainer input_;
    CommonContainer common_;

    double duty_per;  //[%]
    double skip_time_s;
    // bool control_on = false;

    void update(const InputContainer& input) {
        common_ = input.common_;
    }
    // const String toString() const;

    const String toString() const {
        return toStringHelper("duty_per", duty_per) +
               //    "target_temp" + String(target_temp) +
               toStringHelper("skip_time_s", skip_time_s)
            // +
            //    toStringHelper("control on", control_on)
            ;
    }
};

#endif