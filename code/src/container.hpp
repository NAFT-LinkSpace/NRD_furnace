#ifndef CONTAINER_HEAEDER_FILE
#define CONTAINER_HEAEDER_FILE

#include <Arduino.h>
struct CommonContainer {
    unsigned long now_ms;
    double current_tempT0;  //[℃]
    double current_tempT1;  //[℃]
    double current_tempT2;  //[℃]

    const String toString() const {
        return "now_ms" + String(now_ms) +
               "current temp T0:" + String(current_tempT1) +
               "T1:" + String(current_tempT2) +
               "T2" + String(current_tempT2);
    }
};
struct InputContainer {
   public:
    // String command;
    String message;

    int bottun_count;
    CommonContainer common_;

    const String toString() const {
        return "message:" + message +
               "bottun count" + String(bottun_count);
    }
};

class OutputContainer {
   public:
    // InputContainer input_;
    CommonContainer common_;

    double duty_per;  //[%]
    double skip_time_s;
    bool control_on = false;

    void update(const CommonContainer& common) {
        common_ = common;
    }
    // const String toString() const;

    const String toString() const {
        return "duty" + String(duty_per) +
               //    "target_temp" + String(target_temp) +
               "skip_time_s" + String(skip_time_s) +
               "control on" + String(control_on);
    }
};

#endif